#include "esp_camera.h"           // Camera control for ESP32-CAM
#include <WiFi.h>                 // Wi-Fi library for network connection
#include <ESPAsyncWebServer.h>    // Asynchronous web server for handling HTTP requests
#include "SPIFFS.h"               // SPI Flash File System support for image storage
#include <Arduino.h>              // Core Arduino functions and types
#include <FS.h>                   // File system functions
#include <esp_timer.h>            // Timer functions
#include "esp_log.h"              // ESP32 log output
#include "img_converters.h"       // Image format conversions
#include "fb_gfx.h"               // Framebuffer graphics library
#include "fd_forward.h"           // Face detection forward function
#include "fr_forward.h"           // Face recognition forward function
#include "dl_lib.h"               // Deep learning library
#include <soc/soc.h>              // ESP32 SoC functions
#include <soc/rtc_cntl_reg.h>     // Real-time clock control register

// Network credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// Initialize web server on port 80
AsyncWebServer server(80);
// Camera pin definitions (for ESP32-CAM AI-Thinker)
#define PWDN_GPIO_NUM    -1
#define RESET_GPIO_NUM   -1
#define XCLK_GPIO_NUM    4
#define SIOD_GPIO_NUM    18
#define SIOC_GPIO_NUM    23
#define Y9_GPIO_NUM      36
#define Y8_GPIO_NUM      39
#define Y7_GPIO_NUM      35
#define Y6_GPIO_NUM      34
#define Y5_GPIO_NUM      32
#define Y4_GPIO_NUM      5
#define Y3_GPIO_NUM      19
#define Y2_GPIO_NUM      21
#define VSYNC_GPIO_NUM   25
#define HREF_GPIO_NUM    26
#define PCLK_GPIO_NUM    22

void startCameraServer() {
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/index.html", "text/html");
    });
    server.begin();
}

void setup() {
    Serial.begin(115200);

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    // Initialize camera
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;

    // Set frame size
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;

    // Initialize the camera
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("Camera init failed with error 0x%x", err);
        return;
    }

    // Start server
    startCameraServer();
}

void loop() {
    // Empty loop as the AsyncWebServer handles requests
}
