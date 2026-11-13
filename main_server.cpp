#include <iostream>
#include <string>
#include <sstream>
#include <winsock2.h>
#include <cstdlib>



using namespace std;
// Stores student lifestyle preferences
class Preferences {
private:
    int sleepSchedule;
    int studyHabit;
    int cleanliness;
    int noiseTolerance;
    int visitorFrequency;

public:
    Preferences(int sleep, int study, int clean,
                int noise, int visitors) {
        sleepSchedule = sleep;
        studyHabit = study;
        cleanliness = clean;
        noiseTolerance = noise;
        visitorFrequency = visitors;
    }

    int getSleep() const { return sleepSchedule; }
    int getStudy() const { return studyHabit; }
    int getCleanliness() const { return cleanliness; }
    int getNoise() const { return noiseTolerance; }
    int getVisitors() const { return visitorFrequency; }
};

// Stores student information
class Student {
private:
    string name;
    Preferences preferences;

public:
    Student(string studentName, Preferences p)
        : name(studentName), preferences(p) {
    }

    string getName() const {
        return name;
    }

    Preferences getPreferences() const {
        return preferences;
    }
};

// Calculates compatibility between two students
class CompatibilityEngine {
public:

    static double compare(int a, int b, double weight) {
        int difference = abs(a - b);

        if (difference == 0)
            return weight;
        else if (difference == 1)
            return weight * 0.5;
        else
            return 0;
    }

    static double calculateScore(Student s1, Student s2) {
        Preferences p1 = s1.getPreferences();
        Preferences p2 = s2.getPreferences();

        double score = 0;

        score += compare(p1.getSleep(), p2.getSleep(), 30);
        score += compare(p1.getStudy(), p2.getStudy(), 25);
        score += compare(p1.getCleanliness(), p2.getCleanliness(), 20);
        score += compare(p1.getNoise(), p2.getNoise(), 15);
        score += compare(p1.getVisitors(), p2.getVisitors(), 10);

        return score;
    }
};

// Detects differences between student preferences
class ConflictDetector {
public:

    static string getConflicts(Student s1, Student s2) {
        Preferences p1 = s1.getPreferences();
        Preferences p2 = s2.getPreferences();

        string result = "";
        bool conflictFound = false;

        if (p1.getSleep() != p2.getSleep()) {
            result += "<p><strong>Conflict:</strong> Different sleep schedules</p>";
            result += "<p><strong>Suggestion:</strong> Establish quiet hours at night and respect each other's sleep routines.</p>";
            conflictFound = true;
        }

        if (p1.getStudy() != p2.getStudy()) {
            result += "<p><strong>Conflict:</strong> Different study preferences</p>";
            result += "<p><strong>Suggestion:</strong> Set designated silent study hours and use headphones when listening to music.</p>";
            conflictFound = true;
        }

        if (p1.getCleanliness() != p2.getCleanliness()) {
            result += "<p><strong>Conflict:</strong> Different cleanliness preferences</p>";
            result += "<p><strong>Suggestion:</strong> Divide cleaning responsibilities and create a weekly cleaning schedule.</p>";
            conflictFound = true;
        }

        if (p1.getNoise() != p2.getNoise()) {
            result += "<p><strong>Conflict:</strong> Different noise tolerance</p>";
            result += "<p><strong>Suggestion:</strong> Set acceptable noise levels and use headphones when needed.</p>";
            conflictFound = true;
        }

        if (p1.getVisitors() != p2.getVisitors()) {
            result += "<p><strong>Conflict:</strong> Different visitor preferences</p>";
            result += "<p><strong>Suggestion:</strong> Discuss visitor limits, timings and give each other advance notice.</p>";
            conflictFound = true;
        }

        if (!conflictFound) {
            result = "<p>No major preference differences found!</p>";
        }

        return result;
    }
};


string getCategoryScores(Student s1, Student s2) {
    Preferences p1 = s1.getPreferences();
    Preferences p2 = s2.getPreferences();

    string names[5] = {
        "Sleep Schedule",
        "Study Habit",
        "Cleanliness",
        "Noise Tolerance",
        "Visitor Frequency"
    };

    int scores[5];

    scores[0] = (int)CompatibilityEngine::compare(
        p1.getSleep(), p2.getSleep(), 100);

    scores[1] = (int)CompatibilityEngine::compare(
        p1.getStudy(), p2.getStudy(), 100);

    scores[2] = (int)CompatibilityEngine::compare(
        p1.getCleanliness(), p2.getCleanliness(), 100);

    scores[3] = (int)CompatibilityEngine::compare(
        p1.getNoise(), p2.getNoise(), 100);

    scores[4] = (int)CompatibilityEngine::compare(
        p1.getVisitors(), p2.getVisitors(), 100);

    stringstream output;

    output << "<div class='category-results'>";
    output << "<h3>Category-wise Compatibility</h3>";

    for (int i = 0; i < 5; i++) {
        output << "<div class='category-item'>";

        output << "<div class='category-heading'>";
        output << "<span>" << names[i] << "</span>";
        output << "<strong>" << scores[i] << "%</strong>";
        output << "</div>";

        output << "<div class='progress-track'>";
        output << "<div class='progress-fill' style='width:"
               << scores[i] << "%'></div>";
        output << "</div>";

        output << "</div>";
    }

    output << "</div>";

    return output.str();
}


// Converts URL-encoded text into normal text
string urlDecode(string text) {
    string result = "";

    for (int i = 0; i < (int)text.length(); i++) {
        if (text[i] == '+') {
            result += ' ';
        }
        else if (text[i] == '%' && i + 2 < (int)text.length()) {
            string hex = text.substr(i + 1, 2);
            char decoded = (char)strtol(hex.c_str(), NULL, 16);
            result += decoded;
            i += 2;
        }
        else {
            result += text[i];
        }
    }

    return result;
}

// Finds a value in the form data
string getValue(string body, string key) {
    string search = key + "=";
    size_t position = body.find(search);

    if (position == string::npos) {
        return "";
    }

    position += search.length();

    size_t end = body.find("&", position);

    if (end == string::npos) {
        end = body.length();
    }

    return urlDecode(body.substr(position, end - position));
}

// Makes student names safe to display in HTML
string htmlEscape(string text) {
    string result = "";

    for (int i = 0; i < (int)text.length(); i++) {
        if (text[i] == '&') result += "&amp;";
        else if (text[i] == '<') result += "&lt;";
        else if (text[i] == '>') result += "&gt;";
        else if (text[i] == '"') result += "&quot;";
        else if (text[i] == '\'') result += "&#39;";
        else result += text[i];
    }

    return result;
}

// Makes HTML safe to place inside a JSON string
string jsonEscape(string text) {
    string result = "";

    for (int i = 0; i < (int)text.length(); i++) {
        if (text[i] == '\\') result += "\\\\";
        else if (text[i] == '"') result += "\\\"";
        else if (text[i] == '\n') result += "\\n";
        else if (text[i] == '\r') result += "\\r";
        else result += text[i];
    }

    return result;
}



int main() {
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "Winsock initialization failed!" << endl;
        return 1;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == INVALID_SOCKET) {
        cout << "Socket creation failed!" << endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (sockaddr*)&serverAddress,
             sizeof(serverAddress)) == SOCKET_ERROR) {
        cout << "Binding failed! Error: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    if (listen(serverSocket, 5) == SOCKET_ERROR) {
        cout << "Listening failed!" << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    cout << "RoomSync server is running on port 8080!" << endl;

    while (true) {
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);

        if (clientSocket == INVALID_SOCKET) {
            cout << "Accept failed!" << endl;
            continue;
        }

        string request = "";
        char buffer[4096];
        int received;

        while ((received = recv(clientSocket, buffer,
                                sizeof(buffer), 0)) > 0) {
            request.append(buffer, received);

            size_t headerEnd = request.find("\r\n\r\n");

            if (headerEnd != string::npos) {
                size_t contentLength = 0;
                size_t lengthPosition = request.find("Content-Length:");

                if (lengthPosition != string::npos) {
                    lengthPosition += 15;
                    while (lengthPosition < request.length() &&
                           request[lengthPosition] == ' ') {
                        lengthPosition++;
                    }
                    contentLength = atoi(request.substr(
                        lengthPosition).c_str());
                }

                size_t bodyStart = headerEnd + 4;

                if (request.length() >= bodyStart + contentLength) {
                    break;
                }
            }
        }

        cout << "Browser request received!" << endl;

        string body = "";
        size_t headerEnd = request.find("\r\n\r\n");

        if (headerEnd != string::npos) {
            body = request.substr(headerEnd + 4);
        }

        string html = "";

        if (request.find("POST ") == 0) {
            string name1 = getValue(body, "name1");
            string name2 = getValue(body, "name2");

            int p1[5], p2[5];
            bool valid = !name1.empty() && !name2.empty();

            for (int i = 0; i < 5; i++) {
                string value1 = getValue(body, "p1_" + to_string(i));
                string value2 = getValue(body, "p2_" + to_string(i));

                if (value1.empty() || value2.empty()) {
                    valid = false;
                    break;
                }

                p1[i] = atoi(value1.c_str());
                p2[i] = atoi(value2.c_str());

                if (p1[i] < 1 || p1[i] > 3 ||
                    p2[i] < 1 || p2[i] > 3) {
                    valid = false;
                    break;
                }

                if (i == 1 && (p1[i] > 2 || p2[i] > 2)) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                Preferences pref1(p1[0], p1[1], p1[2], p1[3], p1[4]);
                Preferences pref2(p2[0], p2[1], p2[2], p2[3], p2[4]);

                Student student1(name1, pref1);
                Student student2(name2, pref2);

                double score =
                    CompatibilityEngine::calculateScore(student1, student2);

                html = "<h2>Matching Results</h2>";
                html += "<p>" + htmlEscape(name1) + " and " +
                        htmlEscape(name2) + "</p>";

                html += getCategoryScores(student1, student2);

                stringstream scoreText;
                scoreText << score;

                string status;

if (score >= 80)
    status = "Great Match";
else if (score >= 60)
    status = "Good Match";
else if (score >= 40)
    status = "Moderate Match";
else
    status = "Low Compatibility";

stringstream scoreNumber;
scoreNumber << (int)(score + 0.5);

html += "<div class='score-card'>";

html += "<h3>Overall Compatibility</h3>";

html += "<div class='score-circle' style='--score:"
        + scoreNumber.str() + "%'>";

html += "<div class='score-inner'>";
html += "<strong>" + scoreNumber.str() + "%</strong>";
html += "<span>Compatible</span>";
html += "</div>";

html += "</div>";

html += "<div class='match-status'>" + status + "</div>";

html += "</div>";

                html += "<h3>Potential Conflicts</h3>";
                html += ConflictDetector::getConflicts(student1, student2);
            }
            else {
                html = "<p>Invalid or missing student information.</p>";
            }
        }
        else {
            html = "<p>RoomSync server is running. Submit the forms to compare students.</p>";
        }

        string responseBody = "{\"html\":\"" + jsonEscape(html) + "\"}";

        string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: application/json\r\n"
            "Access-Control-Allow-Origin: *\r\n"
            "Content-Length: " + to_string(responseBody.length()) +
            "\r\n"
            "Connection: close\r\n"
            "\r\n" + responseBody;

        int totalSent = 0;

        while (totalSent < (int)response.length()) {
            int sent = send(clientSocket,
                response.c_str() + totalSent,
                (int)response.length() - totalSent, 0);

            if (sent == SOCKET_ERROR || sent == 0) {
                cout << "Sending response failed!" << endl;
                break;
            }

            totalSent += sent;
        }

        cout << "Response sent!" << endl;
        closesocket(clientSocket);
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}

