#include <Arduino.h>

#include <LiquidCrystal.h>
#include "DHT.h"

const int pin_dht = 3;

float temperature;
float umidade;

DHT dht(pin_dht, DHT11);

const int RS = 12, EN = 11, D4 = 10, D5 = 9, D6 = 8, D7 = 7;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void setup(){
  // Configura o LCD com os número de colunas e linhas
  lcd.begin(16, 2); // 16 colunas e 2 linhas
  // Limpa o LCD
  lcd.clear();
  Serial.begin(9600);
  dht.begin();
}

void loop(){
  // Calcula o tempo decorrido em segundos desde que o Arduino foi iniciado
  delay(2000);

  temperature = dht.readTemperature();
  umidade = dht.readHumidity();

  if (isnan(temperature) || isnan(umidade)) {
    lcd.setCursor(0, 0);
    lcd.print("Erro de leitura");
    lcd.setCursor(0, 1);
    lcd.print("Tente novamente");
    Serial.println("Falha na leitura do Sensor DHT!");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Temp.: ");
    lcd.print(temperature);
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("Umidade: ");
    lcd.print(umidade);
    lcd.print("%");

    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.print(" *C ");
    
    Serial.print("\t"); // tabulação
  
    // Imprime o valor de umidade
    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.print(" %\t"); 
    
    Serial.println();
  }
}