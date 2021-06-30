//Função: inicializa parâmetros de conexão MQTT(endereço do servidor, porta e seta função de callback)
//Parâmetros: nenhum
//Retorno: nenhum
void initMQTT() 
{
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);   //informa qual broker e porta deve ser conectado
    MQTT.setCallback(mqtt_callback);            //Atribui função de callback (função chamada quando chega dados no Topic Subscrito)
}

//Função: função de callback esta função é chamada toda vez que uma informação de um dos tópicos subescritos chega)
//Parâmetros: nenhum
//Retorno: nenhum
void mqtt_callback(char* topic, byte* payload, unsigned int length) 
{
    String msg;
 
    //obtem a string do payload recebido
    for(int i = 0; i < length; i++) 
    {
       char c = (char)payload[i];
       msg += c;
    }
   
    //toma ação dependendo da string recebida:
    //verifica se deve colocar nivel alto de tensão na saída D0:
    //IMPORTANTE: o Led já contido na placa é acionado com lógica invertida (ou seja,
    //enviar HIGH para o output faz o Led apagar / enviar LOW faz o Led acender)
    if (strcmp(topic, TOPIC_SUBSCRIBE1) == 0){
         if (msg.equals("0"))
              {
                  digitalWrite(Relay1, LOW);
                  EstadoSaida1 = false;
                  Serial.println("Off");
              }
           
              //verifica se deve colocar nivel alto de tensão na saída D0:
       else if (msg.equals("1"))
              {
                  digitalWrite(Relay1, HIGH);
                  EstadoSaida1 = true;
                  Serial.println("On");
              }
          
              EnviaEstadoOutputMQTT(1);
    }
     
}

//Função: reconecta-se ao broker MQTT (caso ainda não esteja conectado ou em caso de a conexão cair)
//        em caso de sucesso na conexão ou reconexão, o subscribe dos tópicos é refeito.
//Parâmetros: nenhum
//Retorno: nenhum
void reconnectMQTT() 
{
    while (!MQTT.connected()) 
    {
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT, USER_MQTT, PASSWORD_MQTT)) 
        {
            Serial.println("Conectado com sucesso ao broker MQTT!");
            MQTT.subscribe(TOPIC_SUBSCRIBE1); 
        } 
        else
        {
            Serial.println("Falha ao reconectar no broker.");
            Serial.println("Havera nova tentatica de conexao em 2s");
            delay(2000);
        }
    }
}
