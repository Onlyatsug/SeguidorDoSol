#include <Servo.h>

// Declaração de objetos servo e variáveis
Servo servoHorizontal;
int anguloHorizontal = 5;
int limiteSuperiorHorizontal = 175;
int limiteInferiorHorizontal = 5;

Servo servoVertical;
int anguloVertical = 45;
int limiteSuperiorVertical = 90;
int limiteInferiorVertical = 1;

// Pinos de conexão dos LDRs
int ldrCima = A1;    // LDR cima
int ldrBaixo = A0;   // LDR baixo
int ldrEsquerda = A3; // LDR esquerda
int ldrDireita = A2;  // LDR direita

void setup() {
    // Inicialização dos servos e posições iniciais
    servoHorizontal.attach(10);
    servoVertical.attach(9);
    servoHorizontal.write(anguloHorizontal);
    servoVertical.write(anguloVertical);
    delay(2500);
}

void loop() {
    // Leitura dos valores dos LDRs
    int luzCima = analogRead(ldrCima);
    int luzBaixo = analogRead(ldrBaixo);
    int luzEsquerda = analogRead(ldrEsquerda);
    int luzDireita = analogRead(ldrDireita);

    // Definição de constantes para controle
    int tolerancia = 80;
    int tempoDiferenca = 40;

    // Cálculo das médias das leituras dos LDRs
    int mediaCimaBaixo = (luzCima + luzBaixo) / 2;
    int mediaEsquerdaDireita = (luzEsquerda + luzDireita) / 2;

    int diferencaVertical = mediaCimaBaixo;
    int diferencaHorizontal = mediaEsquerdaDireita;

    // Controle do servo vertical com base na diferença de luz vertical
    if (-1 * tolerancia > diferencaVertical || diferencaVertical > tolerancia) {
        if (abs(luzCima - luzBaixo) > tolerancia) {
            if (luzCima > luzBaixo) {
                anguloVertical++;
                if (anguloVertical > limiteSuperiorVertical) {
                    anguloVertical = limiteSuperiorVertical;
                }
            } else if (luzCima < luzBaixo) {
                anguloVertical--;
                if (anguloVertical < limiteInferiorVertical) {
                    anguloVertical = limiteInferiorVertical;
                }
            }
            servoVertical.write(anguloVertical);
        }
    }

    // Controle do servo horizontal com base na diferença de luz horizontal
    if (-1 * tolerancia > diferencaHorizontal || diferencaHorizontal > tolerancia) {
        if (abs(luzEsquerda - luzDireita) > tolerancia) {
            if (luzEsquerda > luzDireita) {
                anguloHorizontal--;
                if (anguloHorizontal < limiteInferiorHorizontal) {
                    anguloHorizontal = limiteInferiorHorizontal;
                }
            } else if (luzEsquerda < luzDireita) {
                anguloHorizontal++;
                if (anguloHorizontal > limiteSuperiorHorizontal) {
                    anguloHorizontal = limiteSuperiorHorizontal;
                }
            }
            servoHorizontal.write(anguloHorizontal);
        }
    }

    // Atraso antes da próxima leitura e ajuste
    delay(tempoDiferenca);
}
