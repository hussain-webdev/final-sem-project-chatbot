#include <iostream>
#include <string>
#include <cstdlib>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

/* ===================== CHAT MODES ===================== */
enum class ChatMode {
    NORMAL = 1,
    PROGRAMMING,
    MATH,
    ENGLISH
};

/* ===================== SYSTEM PROMPTS ===================== */
string getSystemPrompt(ChatMode mode) {
    switch (mode) {
        case ChatMode::NORMAL:
            return "You are a friendly and casual chatbot.";

        case ChatMode::PROGRAMMING:
            return "You are a professional programming assistant. "
                   "Explain clearly and provide correct, clean code.";

        case ChatMode::MATH:
            return "You are a patient math tutor. "
                   "Explain each step before giving the final answer.";

        case ChatMode::ENGLISH:
            return "You are an English tutor. "
                   "Correct grammar and suggest better sentences.";

        default:
            return "You are a helpful chatbot.";
    }
}

/* ===================== CURL CALLBACK ===================== */
size_t writeCallback(void* contents, size_t size, size_t nmemb, string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

/* ===================== OPENAI CHAT ===================== */
string chatWithAI(const string& userMessage, ChatMode mode) {
    const char* apiKey = getenv("OPENAI_API_KEY");
    if (!apiKey) return "API key not found.";

    CURL* curl = curl_easy_init();
    if (!curl) return "Failed to initialize CURL.";

    string response;

    json requestBody = {
        {"model", "gpt-4.1-mini"},
        {"messages", {
            {{"role", "system"}, {"content", getSystemPrompt(mode)}},
            {{"role", "user"}, {"content", userMessage}}
        }}
    };

    string bodyStr = requestBody.dump();

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(
        headers,
        ("Authorization: Bearer " + string(apiKey)).c_str()
    );

    curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, bodyStr.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);

    if (res != CURLE_OK) return "Request failed.";

    auto jsonResponse = json::parse(response);
    return jsonResponse["choices"][0]["message"]["content"];
}

/* ===================== MODE SELECTION ===================== */
ChatMode chooseMode() {
    int choice;
    cout << "\nChoose Chat Mode:\n";
    cout << "1. Normal Chat\n";
    cout << "2. Programming Helper\n";
    cout << "3. Math Tutor\n";
    cout << "4. English Improver\n";
    cout << "Choice: ";
    cin >> choice;
    cin.ignore();

    return static_cast<ChatMode>(choice);
}

/* ===================== MAIN ===================== */
int main() {
    ChatMode mode = chooseMode();
    string input;

    cout << "\nType 'mode' to change mode or 'exit' to quit.\n";

    while (true) {
        cout << "\nYou: ";
        getline(cin, input);

        if (input == "exit") break;

        if (input == "mode") {
            mode = chooseMode();
            continue;
        }

        cout << "Bot: " << chatWithAI(input, mode) << endl;
    }

    cout << "\nGoodbye!\n";
    return 0;
}
