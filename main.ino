#define pinS1VERMELHO 13
#define pinS1AMARELO 12
#define pinS1VERDE 11

#define pinS3VERMELHO 7
#define pinS3AMARELO 6
#define pinS3VERDE 5

#define pinS4VERMELHO 4
#define pinS4VERDE 3

const int S1 = 0;
const int S2eS3eS4 = 1;
const int S4 = 2;
const int S5eS6 = 3;

byte estado;
long int tempo;
int botaoPedestrePressionado = 0;

void trocarEstado(int novoEstado){
  estado = novoEstado;
  tempo = millis();
}


void pedestreLiberado(){
  Serial.println("S5 E S6 VERDE");
}

void pedestreBloquado(){
  if(botaoPedestrePressionado){
    Serial.println("S5 E S6 VERMELHO");
    botaoPedestrePressionado = 0;
  }
}

void pinSEMAFOROS1(int pinMostrar){
  digitalWrite(pinS1VERMELHO,0);
  digitalWrite(pinS1AMARELO,0);
  digitalWrite(pinS1VERDE,0);
  digitalWrite(pinMostrar,1);
}

void pinSEMAFOROS3(int pinMostrar){
  digitalWrite(pinS3VERMELHO,0);
  digitalWrite(pinS3AMARELO,0);
  digitalWrite(pinS3VERDE,0);
  digitalWrite(pinMostrar,1);
}

void pinSEMAFOROS4(int pinMostrar){
  digitalWrite(pinS4VERMELHO,0);
  digitalWrite(pinS4VERDE,0);
  digitalWrite(pinMostrar,1);
}

void setup()
{
  //PINS 
  pinMode(pinS1VERMELHO, OUTPUT);
  pinMode(pinS1AMARELO, OUTPUT);
  pinMode(pinS1VERDE, OUTPUT);
  pinMode(pinS3VERMELHO, OUTPUT);
  pinMode(pinS3AMARELO, OUTPUT);
  pinMode(pinS3VERDE, OUTPUT);
  pinMode(pinS4VERMELHO, OUTPUT);
  pinMode(pinS4VERDE, OUTPUT);
  digitalWrite(pinS3VERMELHO,1);
  digitalWrite(pinS4VERMELHO,1);

  Serial.begin(9600);
  tempo=millis();
}
void loop()
{
  if (estado==S1)
  {
    if(millis()-tempo==1000){
      Serial.println("S1 VERDE");
      pinSEMAFOROS1(pinS1VERDE);
    }
    else if(millis()-tempo == 10000){
      Serial.println("S1 AMARELO");
      pinSEMAFOROS1(pinS1AMARELO);

    }
    else if(millis()-tempo == 13000){
        Serial.println("S1 VERMELHO");
        pinSEMAFOROS1(pinS1VERMELHO);
        trocarEstado(S2eS3eS4);
    }    
  }
  else if (estado==S2eS3eS4)
  {
    if(millis()-tempo==1000){
      Serial.println("S2, S3 e S4 VERDE");
      pinSEMAFOROS3(pinS3VERDE);
      pinSEMAFOROS4(pinS4VERDE);
    }
    if(millis()-tempo == 10000){
      if(botaoPedestrePressionado){
        Serial.println("S4 VERMELHO");
        pinSEMAFOROS4(pinS4VERMELHO);
        pedestreLiberado();
      }
    }
    if(millis()-tempo==12000){
      Serial.println("S2 E S3 AMARELO");
      pinSEMAFOROS3(pinS3AMARELO);
    }
    if(millis()-tempo == 15000){
      Serial.println("S2, S3, S4 VERMELHO");
      pinSEMAFOROS3(pinS3VERMELHO);
      pinSEMAFOROS4(pinS4VERMELHO);
      pedestreBloquado();
      trocarEstado(S1);
    }       
  }
}





