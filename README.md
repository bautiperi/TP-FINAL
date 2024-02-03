# SPACE INVADERS - TRABAJO PRÁCTICO FINAL
*Curso: Programación I (25.02) - Profesores a cargo: Nicolás Magliola, Pablo Daniel Vacatello*

*Integrantes del Grupo: Camila Castro (64694) - Paloma Monserrat Porco Paneiva (64080) - Renzo Amorbello (64071) - Bautista Manuel Peri (64070)*

Hemos desarrollado una implementación del clásico juego SPACE INVADERS utilizando el lenguaje C. Este juego es ejecutable tanto en PC, con una interfaz gráfica, como en Raspberry Pi, con una interfaz de display matricial y joystick.

Nuestra adaptación del juego para PC ha sido inspirada en Barbie, incorporando tonos, animaciones, imágenes y otros elementos que hacen alusión a la temática, sin perder las características esenciales del juego original.

Para lograr esta versatilidad, hemos empleado el mismo backend para ambos frontends, adaptando algunas funciones y definiciones según las características y limitaciones de cada plataforma.

La estructura de nuestro repositorio en Github cuenta con tres ramas distintas, lo que nos permite desarrollar y probar de manera más eficiente cada interfaz:
- **Main**: Esta rama combina ambos proyectos, para PC y Raspberry Pi.
- **Allegro**: Contiene todo el backend y frontend destinado para la ejecución en PC.
- **Raspberry**: Esta rama contiene tanto el backend como el frontend diseñado específicamente para la plataforma Raspberry Pi.

<p align="center">
  <img src="https://i.imgur.com/zaon42X.png">
</p>
