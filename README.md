# Modified-Photochemical-Reflectance-index-MPRI-
## Project Overview
This project measures the Modified Photochemical Reflectance Index (MPRI) to assess vegetation health using an ESP32-CAM module. Captured images are processed using Python and OpenCV to calculate MPRI values, providing insights into photosynthetic activity and potential plant stress.

## Objective
- Capture high-resolution images of vegetation using an ESP32-CAM.
- Transmit the images to a server via Wi-Fi and analyze them using digital image processing.
- Calculate the MPRI to evaluate vegetation health, focusing on photosynthetic activity and stress detection.

## System Requirements
- **Hardware**: ESP32-CAM module, Power supply, Wi-Fi network.
- **Software**:
  - Arduino IDE (for programming the ESP32-CAM).
  - Python (with required libraries like OpenCV, NumPy, and Matplotlib).
## Installation and Setup

### 1. ESP32-CAM Setup
1. Connect the ESP32-CAM module and configure the necessary pin assignments in `main_code.ino`.
2. In Arduino IDE, install the necessary libraries:
   - `ESPAsyncWebServer`, `WiFi`, and `SPIFFS` for handling web server and storage.
3. Replace the SSID and password in `main_code.ino` with your Wi-Fi network credentials.
4. Upload the code to the ESP32-CAM using a USB adapter.
5. Access the server's IP address (printed in the Serial Monitor) to view the image capture page.

### 2. Server HTML Page
- Place `index.html` in the `/server` directory and upload it to SPIFFS on the ESP32-CAM. This page displays the image captured by the ESP32-CAM.

### 3. Python Setup
1. Install required Python libraries:
   ```bash
   pip install opencv-python-headless numpy matplotlib

   Run the script:
bash
Copy code
python image_processing.py
Sample Output
The output displays the original image, MPRI map, and thresholded binary image. A calculated vegetation percentage indicates areas with active photosynthesis or potential stress factors.
