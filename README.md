C++ OpenAI Chatbot

A console-based multi-mode AI chatbot built in C++, integrated with the OpenAI API using libcurl for HTTP requests and nlohmann-json for JSON parsing.
The chatbot supports different conversation modes such as general chat, programming help, math tutoring, and English improvement.

Features

🤖 AI-powered chatbot using OpenAI API

🧠 Multiple chat modes:

Normal Chat

Programming Helper

Math Tutor

English Improver

🌐 REST API integration using libcurl

📄 JSON handling using nlohmann-json

🔐 Secure API key handling via environment variables

🪟 Fully compatible with Windows (g++)

Technologies Used

C++ (g++)

OpenAI API

libcurl

nlohmann-json

vcpkg

PowerShell / Command Prompt

Project Structure
final-sem-project-chatbot/
│
├── chatbot.cpp        # Main chatbot source code
├── chatbot.exe        # Compiled executable
├── libcurl-x64.dll    # Required runtime DLL
├── README.md          # Project documentation

Prerequisites

Windows OS

g++ compiler

Visual Studio Build Tools (C++ workload)

vcpkg package manager

OpenAI API key

Library Installation (vcpkg)
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg install curl nlohmann-json

Environment Variable Setup

Store your OpenAI API key securely:

setx OPENAI_API_KEY "your_openai_api_key_here"


Restart the terminal after setting the variable.

Compile Command

Run this inside your project folder:

g++ chatbot.cpp -IC:\vcpkg\installed\x64-windows\include ^
-LC:\vcpkg\installed\x64-windows\lib -lcurl -o chatbot


📌 Make sure the required libcurl DLL is copied from:

C:\vcpkg\installed\x64-windows\bin


into your project directory.

Run the Chatbot
.\chatbot

How It Works

User selects a chat mode

User enters a query

Program sends the request to OpenAI API

API response is received in JSON format

Response is parsed and displayed in the console

Common Issues & Fixes

Program runs but shows nothing

Missing DLL → copy libcurl-x64.dll to project folder

curl/curl.h not found

Incorrect include path → verify vcpkg install path

API key not detected

Restart terminal after setting environment variable

Future Improvements

Conversation history (memory)

GUI using Qt or SFML

Voice input/output

Cross-platform Linux support

Author

Hussain Ahmed
Semester Project – Programming Fundamentals
C++ AI Chatbot using OpenAI API
