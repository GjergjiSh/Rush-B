String driver_wish;
String top_servo;
String left_servo;
String right_servo;

void setup()
{
    Serial.begin(115200);
}

void loop()
{

    while (Serial.available()) {

        driver_wish = Serial.readStringUntil('\n');
        left_servo = extract(driver_wish, "!", "%");
        right_servo = extract(driver_wish, "%", "#");
        top_servo = extract(driver_wish, "#", "&");
        if (left_servo != "0") {
            Serial.println(left_servo);
        }
        if (right_servo != "0") {
            Serial.println(right_servo);
        }
        if (left_servo != "0") {
            Serial.println(top_servo);
        }
    }
}

String extract(String str, String start, String finish)
{
    int locStart = str.indexOf(start);
    if (locStart == -1)
        return "";
    locStart += start.length();
    int locFinish = str.indexOf(finish, locStart);
    if (locFinish == -1)
        return "";
    return str.substring(locStart, locFinish);
}
