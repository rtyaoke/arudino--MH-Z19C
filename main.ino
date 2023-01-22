// ArduinoでMH-Z19C(NDIR式CO2センサー)読み取りスクリプト
// 参考記事①) https://toccho.net/2021/05/17/co2mz19c-arduino/


#define pwmPin A0

int prevVal = LOW;
long th, tl, h, l, ppm;

void setup() {
  Serial.begin(9600);
  pinMode(pwmPin, INPUT);
}

void loop() {
  long tt = millis();

  //電圧を取得
  int myVal = digitalRead(pwmPin);

  //パルス長の計測
  if (myVal == HIGH) {
    if (myVal != prevVal) {
      h = tt;
      tl = h - l;
      prevVal = myVal;
    }
  }  else {
    if (myVal != prevVal) {
      l = tt;
      th = l - h;
      prevVal = myVal;
      // MH-Z19Cのデータシートの5ページ目に、下記計算式記載
      // 参考記事①のコードでは、下記の係数 2000 が 5000 になっていて間違っていた？ので注意
      // https://www.winsen-sensor.com/d/files/infrared-gas-sensor/mh-z19c-pins-type-co2-manual-ver1_0.pdf
      ppm = 2000 * (th - 2) / (th + tl - 4);
      // Serial.println("PPM = " + String(ppm));
      Serial.println(ppm);
    }
  }
}
