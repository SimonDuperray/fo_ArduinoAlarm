// on définit les pins sur lesquels on branche nos composants
#define BP 3
#define greenLed 4
#define redLed 5
#define blueLed 6
#define breakBP 7
#define presSensor A0

boolean state; // on définit un booléen pour savoir si il y a quelqu'un dans la maison

void setup() {
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(BP, INPUT_PULLUP); // on utilise la résistance interne de l'Arduino
  pinMode(breakBP, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int StateBP = digitalRead(BP); // on lit l'état du premier bouton poussoir
  delay(500); // on attend 500ms pour ne pas fausser l'acquisition
  int breakornot; // on initialise la variable qui va contenir l'état du bouton de break
  if(StateBP == LOW) // si le premier bouton est enfoncé...
  {
    state = !state; // on change la valeur du state
    if(state == false) // si le state est false...
    {
      Serial.println("Tu es sorti"); // on affiche que la personne est sortie de la maison
      digitalWrite(blueLed, HIGH); // et on allume la led bleue pour "activer" l'alarme
      delay(200); // on attend 200ms
      while(breakornot != LOW) // tant qu'on appuie pas sur le bouton de break...
      {
        int val_presence = analogRead(presSensor); // on récupère la valeur détectée par le sensor
        if(val_presence > 0) // si la valeur est strictement supérieure à 0 (si il y a du mouvement...)
        {
          Serial.print("Intrusion / code : "); // on affiche un message de prévention
          Serial.println(val_presence); // avec la valeur lue par le sensor
          digitalWrite(redLed, LOW); // on éteint la led rouge
          digitalWrite(greenLed, HIGH); // on allume la led verte
        }
        else // sinon...
        {
          Serial.println("RAS"); // on affiche Rien A Signaler
          digitalWrite(redLed, HIGH); // on allume la led rouge
          digitalWrite(greenLed, LOW); // on éteint la led verte
        }
        delay(500); // on attend 500ms
        breakornot = digitalRead(breakBP); // on lit l'état du bouton de break
      }
      Serial.println("On a bien break"); // on affiche un message de confirmation
    }
    else // sinon...
    {
      Serial.println("Tu es rentré"); // on affiche un message pour dire que la personne est rentrée dans la maison
      digitalWrite(blueLed, LOW); // on éteint la led bleue pour "désactiver" l'alarme
      delay(200); // on attend 200ms
    }
  }
}
