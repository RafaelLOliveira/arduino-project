/*
    Projeto final da disciplina Sistemas Microprocessados
*/

#include <Adafruit_SSD1306.h>
#define OLED_Adress 0x3C
#define echoPin 2
#define trigPin 3
Adafruit_SSD1306 display(128, 64);

int alimento_escolhido = 0; // variavel serial
long duracao, distancia;

void setup() {
  Serial.begin(9600);

  //setup sensor ultrassom
  DDRD |= (1 << PD3); // porta 3 como saída
  DDRD |= (0 << PD4); // porta 5 como entrada

  //setup led
  DDRB |= 1 << PB5;// porta 13 como saída

  //setup display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_Adress);
  display.clearDisplay();
}

void loop() {

  iniciaTelaDisplay();

  if (Serial.available() > 0) {
    alimento_escolhido = Serial.read();
    delay(5);

    if (alimento_escolhido == '1' | alimento_escolhido == '2') {

      //ARROZ
      while (alimento_escolhido == '1') {

        //leitura do sensor ultrasônico
        distancia = calculaDistancia(duracao);
        Serial.println("Distancia: " + String(distancia) + " cm");
        delay(1000);

        if (distancia < 20) {
          
          acendeLed();
          
          //alimento esquentando
          float Vr, Vrv, temp;
          temp = esquentaAlimento(Vr, Vrv, temp);
          exibeTemperatura(temp);
          delay(100);

          //confere temperatura ideal
          if (temp > 40) {
            exibeMensagemFinalArroz();
            apagaLed();
            alimento_escolhido--;
            delay(5000);
          }
        }
        else if (distancia > 20) {
          apagaLed();
        }
      }

      //FEIJÃO
      while (alimento_escolhido == '2') {

        //leitura do sensor ultrasônico
        distancia = calculaDistancia(duracao);
        Serial.println("Distancia: " + String(distancia) + " cm");
        delay(1000);

        if (distancia < 20) {
          acendeLed();

          //alimento esquentando
          float Vr, Vrv, temp;
          temp = esquentaAlimento(Vr, Vrv, temp);
          exibeTemperatura(temp);
          delay(100);

          exibeTemperatura(temp);

          //confere temperatura ideal
          if (temp > 50) {
            exibeMensagemFinalFeijao();
            apagaLed();
            alimento_escolhido--;
            delay(5000);
          }
        }
        else if (distancia > 20) {
          apagaLed();
        }
      }
    }
    else {
      exibeMensagemDigiteNovamente();
    }
  }
}




/*
    Funções
*/

void acendeLed() {
  PORTB = PORTB | (1 << PB5); //pino 13 como HIGH
}
void apagaLed() {
  PORTB = PORTB & ~ (1 << PB5); // pino 13 como LOW
}
void iniciaTelaDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 10);
  display.setTextColor(WHITE);
  display.println("ARROZ: DIGITE 1");
  display.println("FEIJAO: DIGITE 2");
  display.display();
  delay(1000);
}

long calculaDistancia(long duration) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  return (duration / 2) / 400;
}

float esquentaAlimento(float Vr, float Vrv, float temp) {
  Vr = analogRead(A0);
  Vrv = Vr * 100 / 1023;
  temp = (120 - Vrv); //tensão de capacitor
  return temp;
}

void exibeTemperatura(float temp) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 10);
  display.setTextColor(WHITE);
  display.println("TEMP: ");
  display.println(temp);
  display.display();
  delay(1000);
}

void exibeMensagemFinalArroz() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 10);
  display.setTextColor(WHITE);
  display.println("Retire o arroz");
  display.display();
}


void exibeMensagemFinalFeijao() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 10);
  display.setTextColor(WHITE);
  display.println("Retire o feijao");
  display.display();
}

void exibeMensagemDigiteNovamente() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 10);
  display.setTextColor(WHITE);
  display.println("NUMERO INVALIDO");
  display.display();
  delay(2000);
}


/*
    Referências:

    https://www.filipeflop.com/blog/uso-de-registradores-na-ide-arduino/
    http://www.squids.com.br/arduino/index.php/projetos-arduino/projetos-squids/basico/270-projeto-80-leitura-de-entrada-utilizando-registradores-de-porta-do-arduino
    https://www.embarcados.com.br/lendo-e-escrevendo-nos-pinos-do-arduino/
    https://www.youtube.com/watch?v=LubYc87S9tQ
    https://www.youtube.com/watch?v=3yyPIa58UUQ&ab_channel=ArnaldoVianaJr
    https://www.youtube.com/watch?v=wk3i6HY3VbE&feature=youtu.be
*/
