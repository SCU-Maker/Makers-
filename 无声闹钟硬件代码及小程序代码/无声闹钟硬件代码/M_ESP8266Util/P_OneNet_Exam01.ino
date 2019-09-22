
#include<RTClib.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Ticker.h>
#include "H_project.h"
#include<Wire.h>

RTC_DS1307 rtc;

//用于保存MQTT时间信息-----
char tem_time[2];
int Y;
int M;
int D;
int H;
int MI;
//------------------------
//用于控制灯的开关状态-----
String com="OFF";
bool sw=0;
void breath()
{
  for(int i=200;i<1000;i++)
  {
    analogWrite(D8,i);
    delay(1);
  }
  for(int i=1000;i>200;--i)
  {
    analogWrite(D8,i);
    delay(1);
  }
}
void change_state(){
 
 if(com=="ON")
  com="OFF";
 else if(com=="OFF")
  com="ON";
 else if(com=="BREATH")
 {
  com="OFF";
  sw=0;
 }
}
//----------------------------
int state;
WiFiClient espClient;

//声明方法
void initSystem();
void initOneNetMqtt();
void callback(char* topic, byte* payload, unsigned int length);

/**
 * 初始化
 */
void setup() {
  attachInterrupt(digitalPinToInterrupt(D3), change_state, FALLING);//设置中断号、响应函数、触发方式
  digitalWrite(D3,HIGH);
  Serial.begin(115200);
  if(!rtc.begin())
  {
    Serial.println("Couldn't find RTC");
  }

  if(!rtc.isrunning())
  {
    Serial.println("RTC is not Running!"); 
    //rtc.adjust(DateTime(2019,7,29,17,12,0));
  }
  //时钟模块部分初始化完毕
  initSystem();
  initOneNetMqtt();
}

void loop() {
  ESP.wdtFeed();
  state = connectToOneNetMqtt();
  if(state == ONENET_RECONNECT){
     //重连成功 需要重新注册
     mqttClient.subscribe(TOPIC,1);
     mqttClient.loop();
  }else if(state == ONENET_CONNECTED){
     mqttClient.loop();
  }
  //连接onenet部分处理完毕
  DateTime now = rtc.now();
  if(((now.year()-2000)==Y)&&(now.month()==M)&&(now.day()==D)&&(now.hour()==H)&&(now.minute()==MI)&&(sw==1))
  {
    com="BREATH";
  }
  if(com=="OFF")

    digitalWrite(D8,LOW);

  else if(com=="ON")

    analogWrite(D8,1000);
    
  while(com=="BREATH")
  {
    breath();
  }

  Serial.print(now.year());
  Serial.print("/");
  Serial.print(now.month());
  Serial.print("/");
  Serial.print(now.day());
  Serial.print("/");
  Serial.print(now.hour());
  Serial.print("/");
  Serial.print(now.minute());
  Serial.print(" ");
  Serial.print(sw);
  Serial.println(com);
  delay(1000);

}

void initSystem(){
    int cnt = 0;
    Serial.begin (115200);
    Serial.println("\r\n\r\nStart ESP8266 MQTT");
    Serial.print("Firmware Version:");
    Serial.println(VER);
    Serial.print("SDK Version:");
    Serial.println(ESP.getSdkVersion());
    wifi_station_set_auto_connect(0);//关闭自动连接
    //ESP.wdtEnable(5000);
    WiFi.disconnect();
    delay(100);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
          delay(500);
          cnt++;
          Serial.print(".");
          if(cnt>=40){
            cnt = 0;
            //重启系统
            delayRestart(1);
          }
    }
   // pinMode(LED_BUILTIN, OUTPUT); 
}

void initOneNetMqtt(){
    mqttClient.setServer(mqttServer,mqttPort);
    mqttClient.setClient(espClient);
    mqttClient.setCallback(callback);

    initOneNet(PRODUCT_ID,API_KEY,DEVICE_ID);
}

void callback(char* topic, byte* payload, unsigned int length) {
  sw=1;
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  char load[20];
  memset(load,0,20*sizeof(char));
  for(int i=0;i<length;++i)
  {
    load[i]=(char)payload[i];
  }
  //Serial.println(load);
  int j=0;int count=1;
  for(int I=0;I<length;++I)
  {
    if(load[I]!=' ')
    {
      tem_time[j]=load[I];
      ++j;
    }
    else
    {
      if(count==1)
        sscanf(tem_time,"%d",&Y);
      if(count==2)
        sscanf(tem_time,"%d",&M);
      if(count==3)
        sscanf(tem_time,"%d",&D);
      if(count==4)
        sscanf(tem_time,"%d",&H);
      if(count==5)
        sscanf(tem_time,"%d",&MI);
        //碰到空格 则拿出数据转换为int
      ++count;
      memset(tem_time,0,2*sizeof(char));
      j=0;
    }
    if(I+1==length)
      sscanf(tem_time,"%d",&MI);
  }
  Serial.print(Y);
  Serial.print("/");
  Serial.print(M);
  Serial.print("/");
  Serial.print(D);
  Serial.print("/");
  Serial.print(H);
  Serial.print("/");
  Serial.print(MI);
  Serial.println();
}
