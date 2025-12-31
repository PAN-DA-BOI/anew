import cv2
import numpy as np
import time
import random
from datetime import datetime

def create_fake_frame(width, height, color=(0, 255, 0), message=""):
    """Create a fake camera frame with a solid color and optional text."""
    frame = np.zeros((height, width, 3), dtype=np.uint8)
    frame[:, :] = color  # Fill with color
    if message:
        cv2.putText(frame, message, (50, 100), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)
    return frame

def generate_fake_sensor_data():
    """Generate fake sensor data for testing."""
    temp = random.uniform(60, 90)  # Fake temperature in Fahrenheit
    humid = random.uniform(30, 80)  # Fake humidity percentage
    gas = random.uniform(0, 100)  # Fake gas level
    lat = 37.7749 + random.uniform(-0.1, 0.1)  # Fake latitude
    lng = -122.4194 + random.uniform(-0.1, 0.1)  # Fake longitude
    now = datetime.now()
    year, month, day, hour, minute, second = now.year, now.month, now.day, now.hour, now.minute, now.second
    return (temp, humid, gas, lat, lng, year, month, day, hour, minute, second)

# Main loop
text_color = (0, 255, 0)  # Green
width, height = 640, 480  # Fake camera resolution

while True:
    # Simulate camera feeds (fake frames)
    frame1 = create_fake_frame(width, height, (0, 255, 0), "Camera 1 (Fake)")
    frame2 = create_fake_frame(width, height, (0, 0, 255), "Camera 2 (Fake)")

    # Simulate sensor data
    (temp, humid, gas, lat, lng, year, month, day, hour, minute, second) = generate_fake_sensor_data()

    # Format sensor data
    date_str = f"{year}-{month:02d}-{day:02d}"
    time_str = f"{hour:02d}:{minute:02d}:{second:02d}"
    lat_str = f"{lat:.6f}"
    lng_str = f"{lng:.6f}"
    temp_str = f"{temp:.1f}°F"
    humid_str = f"{humid:.1f}%"

    # Combine frames and add text
    combined = np.hstack((frame1, frame2))
    cv2.putText(combined, f"DATE: {date_str}", (10, 450), cv2.FONT_HERSHEY_SIMPLEX, 0.7, text_color, 2)
    cv2.putText(combined, f"TIME: {time_str}", (10, 480), cv2.FONT_HERSHEY_SIMPLEX, 0.7, text_color, 2)
    cv2.putText(combined, f"HUMID: {humid_str}", (10, 510), cv2.FONT_HERSHEY_SIMPLEX, 0.7, text_color, 2)
    cv2.putText(combined, f"LAT: {lat_str}", (combined.shape[1] - 200, 450), cv2.FONT_HERSHEY_SIMPLEX, 0.7, text_color, 2)
    cv2.putText(combined, f"LNG: {lng_str}", (combined.shape[1] - 200, 480), cv2.FONT_HERSHEY_SIMPLEX, 0.7, text_color, 2)
    cv2.putText(combined, f"TEMP: {temp_str}", (combined.shape[1] - 200, 510), cv2.FONT_HERSHEY_SIMPLEX, 0.7, text_color, 2)

    # Display the combined image
    cv2.imshow("Dual Camera Feed (Fake)", combined)
    if cv2.waitKey(5) & 0xFF == 27:  # Exit on ESC
        break

# Cleanup
cv2.destroyAllWindows()
