#include <iostream>

#include "SistemaArchivosFAT.hpp"

int main() {
  SistemaArchivosFAT fs;

  // Crear archivo y escribir datos
  fs.crear("file1.txt");
  fs.escribir("file1.txt", "En la actualidad, el crecimiento exponencial de datos es un fenomeno que impacta a diversas industrias. Con el auge de tecnologías como la inteligencia artificial, el big data y el Internet de las Cosas (IoT), las organizaciones enfrentan desafíos significativos para gestionar y almacenar esta gran cantidad de información. La escalabilidad se ha vuelto una necesidad crítica, ya que los sistemas de almacenamiento deben adaptarse a la creciente demanda sin comprometer el rendimiento.Las arquitecturas tradicionales a menudo luchan para manejar flujos de datos masivos, lo que ha llevado al desarrollo de soluciones más eficientes, como el almacenamiento en la nube y las redes de almacenamiento (NAS). Estos sistemas permiten un acceso rápido y seguro a grandes volúmenes de datos, optimizando el uso de recursos. Sin embargo, la implementación de estas tecnologías también conlleva retos, como la seguridad de los datos y la gestión de costos.Es esencial que las organizaciones evalúen sus necesidades y elijan la solución de almacenamiento adecuada para garantizar que puedan escalar y adaptarse a las exigencias del futuro");
  //fs.imprimir();
  // fs.cambiarCursor("file1.txt", 5);
  // fs.escribir("file1.txt", " feliz navidad agregare");
  // fs.imprimir();

  fs.crear("file4.txt");
  fs.crear("file2.txt");
  fs.crear("file3.txt");

  fs.escribir("file4.txt", "Juan Mata, holamundo");
  fs.escribir("file2.txt", "Sebastian Ruiz, holamundo2");
  fs.escribir("file3.txt", "Maria Vargas, holamundo3");
  fs.imprimir();


  return 0;
}