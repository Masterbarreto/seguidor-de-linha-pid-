# seguidor-de-linha-pid


**Descrição:**

Este código implementa um robô seguidor de linha utilizando sensores infravermelhos e um controlador PID. O robô é capaz de seguir linhas pretas ou brancas em uma superfície plana.

**Componentes:**

* Arduino Uno
* Módulo seguidor de linha QTRSensors com 4 sensores
* Ponte H L298N
* 2 Motores DC
* Fonte de alimentação 5V
* Cabos e jumpers

**Funcionalidades:**

* Seguir linha preta
* Seguir linha branca
* Controle de velocidade
* Controle PID

**Instalação:**

1. Conecte os componentes de acordo com o diagrama elétrico.
2. Carregue o código no Arduino Uno.
3. Abra o monitor serial do Arduino IDE para verificar se o robô está funcionando corretamente.

**Uso:**

* Para iniciar o robô, coloque-o sobre a linha que deseja seguir.
* O robô ajustará automaticamente a velocidade e a direção para seguir a linha.
* Você pode ajustar os parâmetros do PID para melhorar o desempenho do robô.

**Parâmetros do PID:**

* Kp: ganho proporcional
* Ki: ganho integral
* Kd: ganho derivativo
<img width=50% src="https://smarti.blog.br/wp-content/uploads/2016/08/PID-570x291.jpg"/>

**Recursos adicionais:**

* Documentação do módulo QTRSensors: <URL inválido removido>
* Tutorial sobre controle PID: <URL inválido removido>

**Observações:**

* Este código é um exemplo e pode ser adaptado de acordo com suas necessidades.
* É importante ajustar os parâmetros do PID para obter um bom desempenho do robô.
* Você pode implementar outras funcionalidades, como:
    * Detecção de obstáculos
    * Navegação em ambientes complexos

**Agradecimentos:**

* Pololu Corporation pelo módulo QTRSensors
* Equipe do Arduino pelo IDE e comunidade

**Licença:**

Este código é licenciado sob a licença MIT.

**Melhorias:**

* Adicionar uma função para calibrar os sensores.
* Implementar um sistema de feedback para o usuário, como LEDs ou sons.
* Criar um manual de instruções mais detalhado.

**Espero que este código seja útil para você!**
