#include<LiquidCrystal.h>
#include<Wire.h>
#include"swController.h"
#include"slaveReceiver.h"

LiquidCrystal lcd(7,12,6,11,8,10,9);
bool monitor_flag[4] = {0, 0, 0, 0};
int taswBL_pin = A3, taswB_pin = A2;
int taswR_pin = A0, taswY_pin = A1;
int Red_led_pin = 2, Blue_led_pin = 3;
int tosw_pin = 4;
byte send_data;
bool taswR = 0, taswY = 0, taswBL = 0, taswB = 0, tosw = 0;
bool pageClear1, pageClear2, pageClear3, pageClear4;
bool state1, state2, state3, state4;

//送られてくるデータ
int reciveData1;
int reciveData2;
int reciveData3;
int reciveData4;
byte page;

//slaveのアドレス
const int i2cAddress = 11;

//オブジェクト生成
swController TaswR;
swController TaswY;
swController TaswBL;
swController TaswB;
swController Tosw;

slaveReceiver i2c(9);

void setup()
{
  pageClear1 = pageClear2 = pageClear3 = pageClear4 = 0;
  Wire.begin(i2cAddress);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
  Serial.begin(115200);
  Wire.setClock(400000UL);
  lcd.begin(16, 4);
  pinMode(taswR_pin, INPUT_PULLUP);
  pinMode(taswY_pin, INPUT_PULLUP);
  pinMode(taswBL_pin, INPUT_PULLUP);
  pinMode(taswB_pin, INPUT_PULLUP);
  pinMode(tosw_pin, INPUT_PULLUP);
  pinMode(Blue_led_pin, OUTPUT);
  pinMode(Red_led_pin, OUTPUT);
}

void loop()
{
  if (page == 0)
  {
    lcd.setCursor(16, 0);
    lcd.print("axis");
    lcd.setCursor(0, 0);
    lcd.print("Xaxis : ");
    lcd.print(reciveData1);  lcd.print("  ");
    lcd.setCursor(0, 1);
    lcd.print("Yaxis : ");
    lcd.print(reciveData2); lcd.print("  ");
    lcd.setCursor(4, 2);
    lcd.print("gyro_now : ");
    lcd.print(reciveData3); lcd.print("  ");
    lcd.setCursor(4, 3);
    lcd.print("gyro_offset : ");
    lcd.print(reciveData4); lcd.print("  ");
    pageClear2 = 1;
    pageClear3 = 1;
    pageClear4 = 1;
    if (pageClear1)
    {
      lcd.clear();
      pageClear1 = 0;
    }
  }
  //////////////////////////////////////////////////////////////
  if (page == 1)
  {
    lcd.setCursor(17, 0);
    lcd.print("pos");
    lcd.setCursor(0, 0);
    lcd.print("Xaxis : ");
    lcd.print(reciveData1);  lcd.print("  ");
    lcd.setCursor(0, 1);
    lcd.print("Yaxis : ");
    lcd.print(reciveData2); lcd.print("  ");
    lcd.setCursor(4, 2);
    lcd.print("moveX : ");
    lcd.print(reciveData3); lcd.print("  ");
    lcd.setCursor(4, 3);
    lcd.print("moveY : ");
    lcd.print(reciveData4); lcd.print("  ");
    pageClear1 = 1;
    pageClear3 = 1;
    pageClear4 = 1;
    if (pageClear2)
    {
      lcd.clear();
      pageClear2 = 0;
    }
  }
  //////////////////////////////////////////////////////////////
  if (page == 2)
  {
    lcd.setCursor(16, 0);
    lcd.print("omni");
    lcd.setCursor(0, 0);
    lcd.print("MoveX : ");
    lcd.print(reciveData1);  lcd.print("  ");
    lcd.setCursor(0, 1);
    lcd.print("MoveY : ");
    lcd.print(reciveData2); lcd.print("  ");
    lcd.setCursor(4, 2);
    lcd.print("TurnX : ");
    lcd.print(reciveData3); lcd.print("  ");
    lcd.setCursor(4, 3);
    lcd.print("NULL : ");
    lcd.print(reciveData4); lcd.print("  ");
    pageClear1 = 1;
    pageClear2 = 1;
    pageClear4 = 1;
    if (pageClear3)
    {
      lcd.clear();
      pageClear3 = 0;
    }
  }
  //////////////////////////////////////////////////////////////
  if (page == 3)
  {
    lcd.setCursor(15, 0);
    lcd.print("motor");
    lcd.setCursor(0, 0);
    lcd.print("mainRoll : ");
    lcd.print(reciveData1);  lcd.print("  ");
    lcd.setCursor(0, 1);
    lcd.print("subRoll : ");
    lcd.print(reciveData2); lcd.print("  ");
    lcd.setCursor(4, 2);
    lcd.print("sheet : ");
    lcd.print(reciveData3); lcd.print("  ");
    lcd.setCursor(4, 3);
    lcd.print("clothesPin : ");
    lcd.print(reciveData4); lcd.print("  ");
    pageClear1 = 1;
    pageClear2 = 1;
    pageClear3 = 1;
    if (pageClear4)
    {
      lcd.clear();
      pageClear4 = 0;
    }
  }
  //////////////////////////////////////////////////////////////

  TaswR.update(digitalRead(taswR_pin));
  TaswY.update(digitalRead(taswY_pin));
  TaswBL.update(digitalRead(taswBL_pin));
  TaswB.update(digitalRead(taswB_pin));
  Tosw.update(digitalRead(tosw_pin));

  taswR = TaswR.getData();
  taswY = TaswY.getData();
  taswB = TaswB.getData();
  taswBL = TaswBL.getData();
  tosw  = Tosw.getData();
  if (tosw)
  {
    digitalWrite(Red_led_pin, LOW);
    digitalWrite(Blue_led_pin, HIGH);
  }
  else
  {
    digitalWrite(Red_led_pin, HIGH);
    digitalWrite(Blue_led_pin, LOW);
  }
  reciveData1 = i2c.getData(0) << 8 | i2c.getData(1);
  reciveData2 = i2c.getData(2) << 8 | i2c.getData(3);
  reciveData3 = i2c.getData(4) << 8 | i2c.getData(5);
  reciveData4 = i2c.getData(6) << 8 | i2c.getData(7);
  page = i2c.getData(8);

  bitWrite(send_data, 0, tosw);
  bitWrite(send_data, 1, taswR);
  bitWrite(send_data, 2, taswY);
  bitWrite(send_data, 3, taswB);
  bitWrite(send_data, 4, taswBL);

  //  i2c.show();
  //  Serial.print("RB "); Serial.print(taswR); Serial.print("\t");
  //  Serial.print("YB "); Serial.print(taswY); Serial.print("\t");
  //  Serial.print("BB "); Serial.print(taswB); Serial.print("\t");
  //  Serial.print("BLB "); Serial.print(taswBL); Serial.print("\t");
  //  Serial.print(tosw); Serial.print("\t");
  //  Serial.print(reciveData1);  Serial.print("\t");
  //  Serial.print(reciveData2); Serial.print("\t");
  //  Serial.print(reciveData3); Serial.print("\t");
  //  Serial.print(reciveData4); Serial.print("\t");
  Serial.print(page);
  //  Serial.print(send_data, BIN);
  Serial.println("");
}

void requestEvent()
{
  Wire.write(send_data);
}
void receiveEvent(int any)
{
  i2c.Update();
}
