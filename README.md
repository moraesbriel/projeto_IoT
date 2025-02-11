# Sistema de Monitoramento de Temperatura e Umidade em Armazéns

Este projeto implementa um sistema de IoT para monitoramento de temperatura e umidade em ambientes de armazenamento. Utiliza uma ESP32 para coletar dados de um sensor DHT22 e controla um relé para acionamento de dispositivos de ventilação ou resfriamento. A comunicação ocorre via MQTT e Adafruit IO, permitindo monitoramento e controle remotos.

## Código e Documentação

O código principal está localizado na pasta `code.ino` e foi desenvolvido na Arduino IDE. O arquivo `Sistema de Monitoramento de Temperatura e Umidade` inclui o documento especificando detalhadamente os módulos de conexão Wi-Fi, configuração do MQTT e funções de coleta de dados e controle do relé.

## Hardware

- **Placa ESP32**: Utilizada para a conexão de internet e controle do sensor e atuador.
- **Sensor DHT22**: Responsável pela coleta de dados de temperatura e umidade.
- **Relé**: É acionado quando a temperatura atinge um limite configurado, podendo acionar dispositivos externos.

## Interfaces e Protocolos de Comunicação

O sistema utiliza o protocolo **MQTT** para comunicação com a plataforma **Adafruit IO**. São utilizados os seguintes tópicos MQTT:
- **Feed de Temperatura**: Envia os valores de temperatura em intervalos regulares.
- **Feed de Umidade**: Envia os valores de umidade.
- **Feed de Controle do Relé**: Permite controle remoto do relé via interface do Adafruit IO.

Cada feed é atualizado automaticamente conforme as leituras do sensor e condições de controle do relé.

## Protocolo MQTT e Comunicação TCP/IP

A comunicação do sistema é feita pela rede Wi-Fi (TCP/IP) e utiliza o protocolo MQTT para envio e recebimento de dados. A configuração inclui:
1. **Credenciais do Wi-Fi**: Configure sua `rede_wifi` e `senha_wifi` para conexão com a internet.
2. **Credenciais do Adafruit IO**: Configure seu `usuario_adafruit` e `chave_adafruit` para autenticação MQTT.
3. **Feeds MQTT**: Crie os feeds de temperatura, umidade e controle do relé no Adafruit IO.
