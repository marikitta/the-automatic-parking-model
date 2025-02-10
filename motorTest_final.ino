#define BARCODE_SERIAL    Serial1
char idcar[3]={'0','0','0'};
char i='0';
int k=0;
bool flag=false;
#define IN2 7
#define ENA 6
void setup()
{
  pinMode (ENA, OUTPUT); 

  pinMode (IN2, OUTPUT);
  Serial.begin(9600);
  while (!Serial) {
  }
  BARCODE_SERIAL.begin(9600);
  Serial.println("Парковка в режиме ожидания");
}
void loop()
{
  //Serial.println("Разрешена загрузка");
  // Задаём направление
  delay(1000);
  digitalWrite (IN2, LOW);
  // Регулируем разгон ШИМом, обеспечиваем задержками плавный разгон
  if (BARCODE_SERIAL.available() && flag==false ) {
   
      i=BARCODE_SERIAL.read();
    if (i != '\r' && i != '\n'){
        idcar[k]=i;
        k=k+1;
    }
    if (k==3){
      Serial.print("Car ID : ");
      //Serial.print(idcar[0]);
      //Serial.print(idcar[1]);
      //Serial.println(idcar[2]);
      Serial.println(idcar);
      if (idcar[0]=='1'&& idcar[1]=='1' && idcar[2]=='1' && flag==false){
         Serial.println("QR-код отсканирован. Разрешена загрузка");
            analogWrite(ENA,80);
            delay(460);
            analogWrite(ENA,0);
            delay(10000);
            analogWrite(ENA,95);
            delay(1700);
            flag=true;
      }
    k=0;
  }
  }
  if (flag==true){
    analogWrite(ENA,70);
    Serial.println("Хранение");
  }
  if (BARCODE_SERIAL.available() && flag==true ) {
   
      i=BARCODE_SERIAL.read();
    if (i != '\r' && i != '\n'){
        idcar[k]=i;
        k=k+1;
    }
    if (k==3){
      Serial.print("Car ID : ");
      //Serial.print(idcar[0]);
      //Serial.print(idcar[1]);
      //Serial.println(idcar[2]);
      Serial.println(idcar);
      if (idcar[0]=='1'&& idcar[1]=='1' && idcar[2]=='1' && flag==true){
         Serial.println("Разрешена выгрузка");
        analogWrite(ENA,0);
        delay(2000);
        analogWrite(ENA,0);
        delay(8000);
            //analogWrite(ENA,80);
            //delay(705);
            //analogWrite(ENA,0);
            //delay(7000);
            //analogWrite(ENA,95);
            //delay(1700);
            flag=false;
      }
    k=0;
  }
  }
}