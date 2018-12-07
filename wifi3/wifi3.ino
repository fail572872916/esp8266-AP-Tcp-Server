#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#define MAX_SRV_CLIENTS 3
//最大同时连接数，即可接入的设备数量的最大值，
//8266 tcpserver只能接入5个（此数据不确定，网上是这么说的）
WiFiServer server(8266); //端口号，范围  0-65535
WiFiClient serverClients[MAX_SRV_CLIENTS];
const char WiFiAPPSW[] = "12345678";
//设置AP模式下模块所发出的WIFI的密码
char data[1500];
IPAddress local_IP(192, 168, 0, 159);
IPAddress gateway(192, 168, 4, 9);
IPAddress subnet(255, 255, 255, 0);
#define AP_SSID "AP_Lmln_Bale" //这里改成你的AP名字

#define AP_PSW  "12345678" //这里改成你的AP密码 8位以上
void setupWiFi() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(AP_SSID, AP_PSW);
  Serial.println(); Serial.print ( "IP address: " );
  Serial.println ( WiFi.softAPIP() );
  server.begin();
  //关闭小包合并包功能，不会延时发送数据
  server.setNoDelay(true);
}
void setup() {
  Serial.begin(115200);
  Serial.println ("\nBegin now!!!");
  setupWiFi();
}
void loop()
{
  uint8_t i;
  //检测服务器端是否有活动的客户端连接
  if (server.hasClient()) {
    for (i = 0; i < MAX_SRV_CLIENTS; i++)
      //查找空闲或者断开连接的客户端，并置为可用
    {
      if (!serverClients[i] || !serverClients[i].connected())
      {
        if (serverClients[i]) serverClients[i].stop();
        //未连接,就释放
        serverClients[i] = server.available();
        //分配新的 //
        Serial.print("New client: ");
        Serial.println( );
        continue;
      }
    }
    //若没有可用客户端，则停止连接
    WiFiClient serverClient = server.available();
    serverClient.stop();

  }
  //检查客户端的数据
  for (i = 0; i < MAX_SRV_CLIENTS; i++) {
    if (serverClients[i] && serverClients[i].connected())
    {
      if (serverClients[i].available()) {
        //从Telnet客户端获取数据
        while (serverClients[i].available()) {
          Serial.write(serverClients[i].read());
          //读取client端发送的字符
        }
        Serial.println();
        serverClients[i].print("OK! Got your request.");
        //在client端回复
      }
    }
  }
  if (Serial.available())
  {
    size_t len = Serial.available();
    uint8_t sbuf[len];
    Serial.readBytes(sbuf, len);
    //push UART data to all connected telnet clients
    for (i = 0; i < MAX_SRV_CLIENTS; i++)
    {
      if (serverClients[i] && serverClients[i].connected())
      {
        serverClients[i].write(sbuf, len);
        delay(1);
      }
    }

//
//
//
////   发送到指定客户端。
//    if (serverClients[0] && serverClients[0].connected())
//    {
//      serverClients[0].write(sbuf, len);//向所有客户端发送数据
//      delay(1);
//    }
  }

}
