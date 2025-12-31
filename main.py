import spidev
import struct
import cv2
import numpy as np
import time
from datetime import datetime

# SPI
spi = spidev.SpiDev()
spi.open(0, 0)  # Bus 0, Device 0 (CE0)
spi.max_speed_hz =1000000  # 1 MHz

sensor_data_fmt = 'ffffiiiiii'  # 6 floats, 6 ints
sensor_data_size = struct.calcsize(sensor_data_fmt)

def read_sensor_data():
    spi.xfer([0x00] * sensor_data_size)  # send bytes to sense
    data = spi.readbytes(sensor_data_size)
    return struct.unpack(sensor_data_fmt, bytes(data))

def create_placeholder_frame(width, height, message="No Camera Info"):
    frame = np.zeros((height, width, 3), dtype=np.uint8)
    cv2.putText(frame, message, (50, 100), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)
    return frame

# Initialize cameras
cap1 = cv2.VideoCapture(0)  # Adjust index as needed
cap2 = cv2.VideoCapture(1)  # Adjust index as needed
text_color = (0, 255, 0)  # Green

while True:
    # Read frames from cameras
    ret1, frame1 = cap1.read()
    ret2, frame2 = cap2.read()

    if not ret1:
        frame1 = create_placeholder_frame(640, 480, "Camera 1: No Signal")
        # Try to reconnect camera 1
        cap1.release()
        time.sleep(4)
        cap1 = cv2.VideoCapture(0)

    if not ret2:
        frame2 = create_placeholder_frame(640, 480, "Camera 2: No Signal")
        # Try to reconnect camera 2
        cap2.release()
        time.sleep(4)
        cap2 = cv2.VideoCapture(1)

    # Read sensor data from Arduino
    try:
        (temp, humid, gas, lat, lng, year, month, day, hour, minute, second) = read_sensor_data()
    except:
        (temp, humid, gas, lat, lng) = ("N/A", "N/A", "N/A", "37.7749", "-122.4194")
        (year, month, day, hour, minute, second) = (2025, 1, 1, 12, 0, 0)

    # Format sensor data
    date_str = f"{year}-{month:02d}-{day:02d}"
    time_str = f"{hour:02d}:{minute:02d}:{second:02d}"
    lat_str = f"{lat:.6f}"
    lng_str = f"{lng:.6f}"
    temp_str = f"{temp:.1f}°F"
    humid_str = f"{humid:.1f}%"

    # Add text to frames
    combined = np.hstack((frame1, frame2))
    cv2.putText(combined, f"DATE: {date_str}", (10, 450), cv2.FONT_HERSHEY_SIMPLEX, 0.7, text_color, 2)
    cv2.putText(combined, f"TIME: {time_str}", (10, 480), cv2.FONT_HERSHEY_SIMPLEX, 0.7, text_color, 2)
    cv2.putText(combined, f"HUMID: {humid_str}", (10, 510), cv2.FONT_HERSHEY_SIMPLEX, 0.7, text_color, 2)
    cv2.putText(combined, f"LAT: {lat_str}", (combined.shape[1] - 200, 450), cv2.FONT_HERSHEY_SIMPLEX, 0.7, text_color, 2)
    cv2.putText(combined, f"LNG: {lng_str}", (combined.shape[1] - 200, 480), cv2.FONT_HERSHEY_SIMPLEX, 0.7, text_color, 2)
    cv2.putText(combined, f"TEMP: {temp_str}", (combined.shape[1] - 200, 510), cv2.FONT_HERSHEY_SIMPLEX, 0.7, text_color, 2)

    # Display the combined image
    cv2.imshow("Dual Camera Feed", combined)
    if cv2.waitKey(5) & 0xFF == 27:  # Exit on ESC
        break

# Release resources
cap1.release()
cap2.release()
cv2.destroyAllWindows()
spi.close()
