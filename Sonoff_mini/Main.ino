//Função: envia ao Broker o estado atual do output 
//Parâmetros: int numberOut
//Retorno: nenhum
void EnviaEstadoOutputMQTT(int numberOut)
{
  if(numberOut == 1){
     if (!EstadoSaida1)
      MQTT.publish(TOPIC_PUBLISH1, "0");
 
     if (EstadoSaida1)
      MQTT.publish(TOPIC_PUBLISH1, "1");
      
  }

}


void checkSwitch()
{

  bool tecla1 = digitalRead(S1);
  if (tecla1 != tecla1_anterior)
  {

    if (millis() - tempo_tecla1_anterior_Millis >= 250)
    {
      tempo_tecla1_anterior_Millis = millis();
      tecla1_anterior = tecla1;
      EstadoSaida1 = !digitalRead(Relay1);
      digitalWrite(Relay1, EstadoSaida1);  // invert o valor do rele"
      Serial.print("Estado Rele: ");
      Serial.println(EstadoSaida1);
      EnviaEstadoOutputMQTT(1);
    }
      
   }
}
