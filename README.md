# 🌐 ESP32 Long-Distance Communication with Firebase

This project demonstrates how to send real-time data between two **ESP32 microcontrollers** using **Google Firebase** as a cloud-based bridge. It's designed for scenarios where devices are physically far apart but need to stay synced — ideal for **remote sensing**, **IoT communication**, and **wearable interaction**.

---

## 🎯 Overview

- Uses **Google Firebase Realtime Database** to sync data across devices.
- Connects two ESP32 boards: one with a button, the other with an LED.
- When a button is pressed on one board, an LED on the second board reacts — even over long distances.
- Built using **Arduino IDE**, with WiFi and Firebase libraries.

---

## 🧰 Tools & Libraries

- Google Firebase Realtime Database  
- ESP32 WiFi-enabled microcontrollers  
- Arduino IDE + Firebase Client Library for ESP  

---

## 🧠 How It Works

- Each ESP32 device connects to Firebase via **NodeMCU + WiFi**.
- When the button is pressed on one ESP32, the state (`0` or `1`) is uploaded to the database.
- The second ESP32 constantly checks the database for updates.
- If the button state changes, the LED reacts in real time — giving the illusion of direct long-distance interaction.

---

## 🎬 Watch our Demo

📹 [Watch on YouTube](https://www.youtube.com/watch?v=Xx5cEIbBvZY)

---

## 💻 Screenshot

<img src="Image.jpg" alt="ESP32 Firebase Project Screenshot" width="600"/>
