// ESP32_with_Blynk_app

//Thắng
#define BLYNK_TEMPLATE_ID "TMPL6fBDQrwNM"
#define BLYNK_TEMPLATE_NAME "led on off"
char auth[] = "w9uz1XrOwDrNVZgM3H01AMOK-wIV0XmD";

// Phát
// #define BLYNK_TEMPLATE_ID "TMPL6u6GUFE3m"
// #define BLYNK_TEMPLATE_NAME "Smart Switch"
// char auth[] = "036NJDozDLNNIj-Tov9n7jYbaKn_OA7n";

// Include the library files
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Enter your WIFI SSID and password
// char ssid[] = "LE";
// char pass[] = "13112004";

// Enter your WIFI SSID and password
char ssid[] = "HUIT_SV";
char pass[] = "";

// --- BƯỚC 1: KHAI BÁO CHÂN LED, KÊNH PWM VÀ CÁC BIẾN TRẠNG THÁI ---
const int ledPin1 = 2;
const int ledPin2 = 4;
const int ledPin3 = 5;

// Biến lưu độ sáng của mỗi đèn
int brightness1 = 255; // Độ sáng mặc định khi bật
int brightness2 = 255;
int brightness3 = 255;

// Biến lưu trạng thái Bật/Tắt của mỗi đèn
bool state1 = false; // Mặc định là Tắt
bool state2 = false;
bool state3 = false;

// Cài đặt thông số cho PWM
const int freq = 5000;
const int resolution = 8;

// --- BƯỚC 3: HÀM LẮNG NGHE CHO THANH TRƯỢT VÀ NÚT BẤM ---

// Các hàm cho thanh trượt (V3, V4, V5) chỉ cập nhật biến độ sáng
BLYNK_WRITE(V3) {
  brightness1 = param.asInt();
  // Nếu đèn đang bật, cập nhật độ sáng ngay lập tức
  if (state1) {
    ledcWrite(ledPin1, brightness1);
  }
}

BLYNK_WRITE(V4) {
  brightness2 = param.asInt();
  if (state2) {
    ledcWrite(ledPin2, brightness2);
  }
}

BLYNK_WRITE(V5) {
  brightness3 = param.asInt();
  if (state3) {
    ledcWrite(ledPin3, brightness3);
  }
}

// Các hàm cho nút nhấn (V0, V1, V2) điều khiển Bật/Tắt
BLYNK_WRITE(V0) {
  if (param.asInt() == 1) { // Nếu nút được gạt Bật
    state1 = true;
    ledcWrite(ledPin1, brightness1); // Bật đèn với độ sáng đã lưu
  } else { // Nếu nút được gạt Tắt
    state1 = false;
    ledcWrite(ledPin1, 0); // Tắt đèn
  }
}

BLYNK_WRITE(V1) {
  if (param.asInt() == 1) {
    state2 = true;
    ledcWrite(ledPin2, brightness2);
  } else {
    state2 = false;
    ledcWrite(ledPin2, 0);
  }
}

BLYNK_WRITE(V2) {
  if (param.asInt() == 1) {
    state3 = true;
    ledcWrite(ledPin3, brightness3);
  } else {
    state3 = false;
    ledcWrite(ledPin3, 0);
  }
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  // --- BƯỚC 2: CẤU HÌNH CÁC KÊNH PWM (API MỚI) ---
  // Sử dụng ledcAttach() thay vì ledcSetup() + ledcAttachPin()
  ledcAttach(ledPin1, freq, resolution);
  ledcAttach(ledPin2, freq, resolution);
  ledcAttach(ledPin3, freq, resolution);
  
  // Tắt tất cả LED ban đầu
  ledcWrite(ledPin1, 0);
  ledcWrite(ledPin2, 0);
  ledcWrite(ledPin3, 0);
}

void loop() {
  Blynk.run();
}