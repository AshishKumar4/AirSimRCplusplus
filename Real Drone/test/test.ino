#include <SPI.h>



#define CPACKET_MAGIC 110
#define REQ_SIGNAL     251
#define ACCEPT_SIGNAL    252
#define RPACKET_MAGIC  120
#define FALSE_PACKET   145

struct ControlPackets
{
  unsigned char magic;
  unsigned char throttle;
  unsigned char pitch;
  unsigned char roll;
  unsigned char yaw;
  unsigned char aux1;
  unsigned char aux2;
  unsigned char switches;
  unsigned char random[9];
  unsigned char checksum;
};

struct ResponsePackets
{
    unsigned char magic;
    unsigned char alt;
    unsigned char pitch;
    unsigned char roll;
    unsigned char yaw;
    unsigned char lat;
    unsigned char lon;
    unsigned char heading;
    unsigned char random[9];
    unsigned char checksum;
};

ControlPackets rfCusData;
ResponsePackets rfResData;
char *buff = (char *)&rfCusData;
char *rbuff = (char *)&rfResData;

volatile int index = 0;
volatile boolean process = true;

void setup(void)
{
  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE);
  // SPI.begin();
  index = 0;
  SPI.attachInterrupt();
  Serial.begin(115200);
  process = true;
}

ISR(SPI_STC_vect)
{
  unsigned char g = SPDR;
  Serial.println(g);
  if (!process) // && (SPSR & (1<<SPIF)) != 0)
  {
    if (index < sizeof(ControlPackets))
    {
      buff[index++] = g;
    }
    else
    {
      //if(buff[0] == 110)
      process = true;

      if (rfCusData.magic == CPACKET_MAGIC)
      {
        Serial.print((int)rfCusData.magic);
        Serial.print(" ");
        Serial.print((int)rfCusData.throttle);
        Serial.print(" ");
        Serial.print((int)rfCusData.pitch);
        Serial.print(" ");
        Serial.print((int)rfCusData.roll);
        Serial.print(" ");
        Serial.print((int)rfCusData.yaw);
        Serial.print("\n");
      }
      else 
      {
        /*for (int i = 0; i < index; i++)
        {
          SPDR = FALSE_PACKET;
        }*/
      }
      //process = false;
      // index = 0;
      // index = 0;
    }
  }
  else if(g == REQ_SIGNAL)  // Handshake
  {
    Serial.println("Got...");
    //buff[0] = g;
    SPDR = ACCEPT_SIGNAL;  // Recieved Signal
    index = 0;
    process = false;
  }
}
void loop()
{
  analogRead(A2);
  /*memcpy(&cp.random, "hello\0", 9);
   char* tt = (char*)&cp;
   SPI_transfer(tt, sizeof(ControlPackets));*/
 /* if(process)
  {
    index = 0;
    //if(cp.magic == 110)// && cp.checksum == checksum(buff, sizeof(ControlPackets)))
    {
      //Serial.print((int)sizeof(ControlPackets));
      //Serial.print("->");
      Serial.print((int)cp.magic);
      Serial.print(" ");
      Serial.print((int)cp.throttle);
      Serial.print(" ");
      Serial.print((int)cp.pitch);
      Serial.print(" ");
      Serial.print((int)cp.roll);
      Serial.print(" ");
      Serial.print((int)cp.yaw);
      Serial.print("\n");
    }
    process = false;
  }//*/
  /*char val=0, tmp;
  while(1)
  {
    tmp = SPI.transfer(val);
    if(tmp == 110)
      break;
  }
  SPI.transfer((void*)buff, (size_t)sizeof(ControlPackets));
//  if(cp.magic == 110)// && cp.checksum == checksum(buff, sizeof(ControlPackets)))
    {
      //Serial.print((int)sizeof(ControlPackets));
      //Serial.print("->");
      //Serial.print((int)cp.magic);
      //Serial.print(" ");
      Serial.print((int)cp.throttle);
      Serial.print(" ");
      Serial.print((int)cp.pitch);
      Serial.print(" ");
      Serial.print((int)cp.roll);
      Serial.print(" ");
      Serial.print((int)cp.yaw);
      Serial.print("\n");
    }*/
}

int SPI_transfer(char* buff, int len)
{
  for(int i = 0; i < len; i++)
  {
    buff[i] = SPDR;
  }
}





