#define BLYNK_TEMPLATE_ID "TMPL6Dpl-Cnjq"
#define BLYNK_TEMPLATE_NAME "ESP 8266"
#define BLYNK_AUTH_TOKEN "sGhJtZMjRnoxhhRqBi1-RcQrpw_VUl3Z"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "doan_nhom4";
char pass[] = "123456789";

// Chân kết nối
#define LED1 D0
#define LED2 D4
#define LED3 D6
#define LED4 D7
#define BUZZER_PIN D5
#define FLAME_PIN D1
#define SMOKE_PIN D2

BlynkTimer timer;

// Trạng thái hệ thống
// 0 = Bình thường
// 1 = Vừa phát hiện cháy/khói, ưu tiên gửi cảnh báo Blynk
// 2 = Đã gửi cảnh báo, bật còi và đèn liên tục
int alarmState = 0;

unsigned long timeFireDetected = 0;
unsigned long lastEventTime = 0;

// Thời gian chống spam event
// Khi test có thể để 10000 = 10 giây
// Khi báo cáo/chạy thật có thể đổi thành 60000 = 60 giây
const unsigned long EVENT_COOLDOWN_MS = 10000;

bool ledState = false;
bool toneHigh = false;

// Lưu trạng thái cảm biến toàn cục
int flameValue = HIGH;
int smokeValue = HIGH;

void setup() {
  Serial.begin(115200);
  delay(100);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(FLAME_PIN, INPUT_PULLUP);
  pinMode(SMOKE_PIN, INPUT_PULLUP);

  turnOffAlarm();

  Serial.println();
  Serial.println("Dang ket noi WiFi va Blynk...");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.println("Da ket noi Blynk.");

  // Đọc cảm biến nhanh
  timer.setInterval(200L, checkSensors);

  // Gửi dữ liệu lên Blynk chậm hơn để tránh spam message
  timer.setInterval(2000L, sendDataToBlynk);

  // Chạy hiệu ứng còi và đèn
  timer.setInterval(300L, runAlarmEffects);
}

void loop() {
  Blynk.run();
  timer.run();
}

// Nút V2 trên Blynk dùng để tắt báo động
BLYNK_WRITE(V2) {
  int buttonValue = param.asInt();

  if (buttonValue == 0) {
    alarmState = 0;
    turnOffAlarm();

    Serial.println("Da nhan lenh TAT bao dong tu App.");
  }
}

void checkSensors() {
  flameValue = digitalRead(FLAME_PIN);
  smokeValue = digitalRead(SMOKE_PIN);

  // Nếu phát hiện lửa hoặc khói và hệ thống đang ở trạng thái bình thường
  if ((flameValue == LOW || smokeValue == LOW) && alarmState == 0) {
    alarmState = 1;
    timeFireDetected = millis();

    Serial.println("!!! PHAT HIEN NGUY HIEM !!!");
    Serial.println("Dang uu tien gui thong bao len Blynk...");

    // Bật nút cảnh báo V2 trên app
    if (Blynk.connected()) {
      Blynk.virtualWrite(V2, 1);
    }

    // Gửi event lên Blynk
    sendFireEvent();
  }

  // Sau khi đã dành thời gian gửi thông báo, bật còi và đèn
  if (alarmState == 1) {
    if (millis() - timeFireDetected > 1500) {
      alarmState = 2;
      Serial.println("Bat dau kich hoat coi va den bao dong.");
    }
  }
}

void sendDataToBlynk() {
  if (Blynk.connected()) {
    Blynk.virtualWrite(V0, smokeValue == LOW ? 1023 : 0);
    Blynk.virtualWrite(V1, flameValue == LOW ? 200 : 0);

    Serial.print("Smoke: ");
    Serial.print(smokeValue == LOW ? "CANH BAO" : "BINH THUONG");
    Serial.print(" | Flame: ");
    Serial.println(flameValue == LOW ? "CANH BAO" : "BINH THUONG");
  } else {
    Serial.println("Blynk mat ket noi, khong gui du lieu duoc.");
  }
}

void sendFireEvent() {
  if (!Blynk.connected()) {
    Serial.println("Blynk chua connected, khong gui duoc event.");
    return;
  }

  if (millis() - lastEventTime > EVENT_COOLDOWN_MS || lastEventTime == 0) {
    if (flameValue == LOW) {
      Blynk.logEvent("fire_alert", "CANH BAO: CO LUA TAI GARAGE!");
      Serial.println("Da gui event: CO LUA.");
    } 
    else if (smokeValue == LOW) {
      Blynk.logEvent("fire_alert", "CANH BAO: CO KHOI TAI GARAGE!");
      Serial.println("Da gui event: CO KHOI.");
    }

    lastEventTime = millis();

    // Ép Blynk xử lý gửi dữ liệu ngay trong vài nhịp
    for (int i = 0; i < 10; i++) {
      Blynk.run();
      delay(50);
    }
  } else {
    Serial.println("Chua het thoi gian cooldown, khong gui event moi.");
  }
}

void runAlarmEffects() {
  if (alarmState == 2) {
    ledState = !ledState;

    digitalWrite(LED1, ledState);
    digitalWrite(LED2, !ledState);
    digitalWrite(LED3, ledState);
    digitalWrite(LED4, !ledState);

    toneHigh = !toneHigh;

    if (toneHigh) {
      tone(BUZZER_PIN, 1200);
    } else {
      tone(BUZZER_PIN, 800);
    }
  }
}

void turnOffAlarm() {
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);

  noTone(BUZZER_PIN);
}