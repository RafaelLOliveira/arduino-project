## Projeto de Arduino da discplina Sistemas Microprocessados usando SimulIDE

### Resumo: 
O projeto consiste na simulação do funcionamento de um micro-ondas. Esse micro-ondas tem como o objetivo emular um alimento esquentando de maneira automática, ou seja, sem que o usuário  precise digitar o tempo de aquecimento do alimento. Assim, quando o alimento atingir a temperatura ideal, o processo de aquecimento será encerrado e evitando um gasto de energia desnecessário.

### Componentes:
* Um sensor ultrasonico HC-SR04, usado para detectar a presença do alimento.
* Um led, para simular a luz interna do micro-ondas.
* Um display SSD 1306, para mostrar informações ao usuário.
* Um circuito RC, para emular o funcionamento de um sensor infravermelho de temperatura, já que o SimulIDE não possui esse componente. A tensão medida no capacitor é a emulação da temperatura do alimento.

### Passo a passo do funcionamento do circuito:
A configuração inicial do circuito deve ser: Chave do RC fechada, potenciômetro com um valor alto de resistência.
1. Inicie a simulação
2. Abra o monitor Serial
3. Uma mensagem aparecerá no display oled. Digite o número do alimento escolhido na serial.
5. Altere o potênciometro para uma baixa resistência, pois isso emulará o usuário colocando o alimento dentro do micro-ondas. O led acenderá automaticamente em seguida.
7. Abra a chave do cirsuito RC.
8. O display oled mostrará a temperatura do alimento subindo, e quando o processo atingir a temperatura ideial, o processo se encerrará.
  
