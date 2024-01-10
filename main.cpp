#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
//bibliotecas usadas

using namespace std;

struct Empleados{
  int codigo;
  char apellido[20];
  char nombre[20];
  long int celular;
};
//estructura de datos para empleados

int menu();
int creararchivobin(Empleados *);
void generarindice(int);
void imprimirbin(int);
void imprimirindice(int);
void archivotxt(int);
int encontrarcantidad(string);
void crearcarta(int);
void anyadirempleado(int);
void operadores(int);
void imprimirope(Empleados *, int, string);
void leeroperadores();
void abrirope(Empleados *ope, string titulo, string operador);
//funciones usadas

int main() {
  int confirmacion=0;
  int opcion;
  Empleados *datos;
  bool creado=false;
  int cantidad;

  do{
    opcion=menu();
    switch(opcion){

        case 1:{
            if(creado==false){
            cantidad=creararchivobin(datos);
            creado=true;
            break;
          }
            else{
              cout<<"Ya tiene un archivo creado bajo ese nombre o ya utilizó esta función, si desea añadir un empleado nuevo marque la opcion 3"<<endl<<endl;
              break;
            }
        }

        case 2:{
          cantidad=encontrarcantidad("datos.bin");
          archivotxt(cantidad);
          break;
        }

        case 3:{
          cantidad=encontrarcantidad("datos.bin");
          anyadirempleado(cantidad);
          break;
        }

        case 4:{
            cantidad=encontrarcantidad("datos.bin");
            archivotxt(cantidad);
            crearcarta(cantidad);
          break;
        }

        case 5:{
          cantidad=encontrarcantidad("datos.bin");
          cout<<"La cantidad de datos encontrados es de "<<cantidad<<endl;
          generarindice(cantidad);
          imprimirbin(cantidad);
          cout<<endl;
          imprimirindice(cantidad);
          cout<<endl;

          break;
        }

        case 6:{
            cantidad=encontrarcantidad("datos.bin");
            operadores(cantidad);
          break;
        }
        case 7:{
            cantidad=encontrarcantidad("datos.bin");
            leeroperadores();
          break;
        }


    }
    cout<<"Si desea usar otra función del menu marque 1, si desea cerrar el programa marque 0"<<endl;
      cin>>confirmacion;

  }while(confirmacion==1);
  cout<<endl<<endl<<endl;
  cout<<"Usted ha finalizado el programa"<<endl;
  cout<<"proyecto realizado por Santiago Camilo Rey // Juan Manuel Duran Rueda "<<endl;
  cout<<"Proyecto 1 programación avanzada 2021"<<endl;

}

int menu(){
  int opcion;
  cout<<"--------MENU--------"<<endl;
  cout<<"OPCIONES:"<<endl;
  cout<<"1. Agregar los datos iniciales en los archivos binarios (datos.bin y índices.bin) "<<endl;
  cout<<"2. Generar un archivo de texto llamado datos.txt, este archivo debe contener los apellidos, nombres y el número del celular de cada empleado en orden alfabético. "<<endl;
  cout<<"3. Adicionar un empleado al archivo datos.bin y a su vez modificar el archivo de índice (índice.bin) para mantener el orden alfabético del archivo empleados"<<endl;
  cout<<"4. Enviar una carta a los empleados de la compañia con el archivo de texto como plantilla "<<endl;
  cout<<"5. Leer un archivo de datos binario y generar el archivo indices.bin a base de este "<<endl;
  cout<<"6. conocer la lista de las compañias de telefonia movil de los empleados de la empresa"<<endl;
  cout<<"7.Leer archivos binarios de operadores para secretaria"<<endl;
  cout<<"Ingrese la opcion que desee usar en el programa"<<endl;
  cin>>opcion;
  return opcion;
}

int creararchivobin(Empleados *datos){

  int cantidad;
  cout<<"Ingrese la cantidad de empleados que quiere añadir"<<endl;
  cin>>cantidad;
  datos= new Empleados[cantidad];

  for(int i=0;i<cantidad;i++){
      cout<<endl<<endl;
            cout<<"ingrese el codigo del empleado "<<i<<endl;
            cin>>(datos+i)->codigo;
            cin.ignore();
            cout<<"ingrese el apellido del empleado "<<i<<endl;
            cin.getline((datos+i)->apellido,20);
            cout<<"ingrese el nombre del empleado "<<i<<endl;
            cin.getline((datos+i)->nombre,20);
            cout<<"ingrese el numero de telefono del empleado"<<endl;
            cin>>(datos+i)->celular;
            cin.ignore();
  }

  //una vez tenido el puntero con los datos almacenados, se guardara en el archivo binario

  ofstream binario;
  binario.open("datos.bin",ios::binary|ios::out|ios::app);
  if(binario.fail()){
    cout<<"no se pudo crear el archivo"<<endl;
  }else{
    for(int i=0;i<cantidad;i++){
        binario.write((char *)(datos+i),sizeof(Empleados));
    }
    binario.close();
    generarindice(cantidad);
    // Se movió el binario.close() de lugar. La función imprimir bin, también crea un
                    // canal de comunicación con un archivo en el FileSystem, y al no cerrar previamente
                   // la que se tenia en binario, genera conflicto.
    imprimirbin(cantidad);
    cout<<endl;
    imprimirindice(cantidad);
    cout<<endl;
  }
 return cantidad;
}

void generarindice(int cantidad){

  Empleados *orden;
  orden= new Empleados[cantidad];

  char** posicion;
  posicion = new char* [cantidad];

  for (int i = 0 ; i < cantidad; i++) {
    *(posicion+i) = new char [20]; // Solicitando tamaño para cada cadena de caracteres
  }


  int *pos;
  pos= new int [cantidad];

  for(int i=0;i<cantidad;i++){
    *(pos+i)=0;
  }

  ifstream binario;
  binario.open("datos.bin",ios::binary|ios::in);


  if(binario.fail()){
    cout<<"no se pudo crear el archivo de nombre datos.bin"<<endl;
  }else{
    for(int i=0;i<cantidad;i++){
      binario.read((char *)(orden+i),sizeof(Empleados));
    }

    //estan bien los apellidos en (orden)


         for(int i=0;i<cantidad;i++){
          strcpy(*(posicion+i),(orden+i)->apellido);
        }

  }
  binario.close();

  ofstream indice;
  indice.open("indice.bin",ios::binary|ios::out);


  if(indice.fail()){
    cout<<"no se pudo crear el archivo de nombre indice.bin"<<endl;
  }else{
      for(int i=0;i<cantidad-1;i++){
        for(int j=0;j<cantidad-1;j++){
          if(strcmp(*(posicion+j),*(posicion+j+1)) > 0) {
            char* aux = *(posicion+j);
            *(posicion+j) =*(posicion+j+1);
            *(posicion+j+1)=aux;
          }
        }
      }

      for(int i=0;i<cantidad;i++){
        for(int j=0;j<cantidad;j++){
          if (strcmp(*(posicion+j),(orden+i)->apellido)==0) {
              pos[j]=i;
              break;
          }
        }
      }
      cout << "\n\n";

    for(int i=0;i<cantidad;i++){
          indice.write((char *)(pos+i),sizeof(int));
    }

      indice.close();
  }
}

void imprimirbin(int cantidad){
  Empleados *imp;
  imp=new Empleados[cantidad];

  ifstream binario;
  binario.open("datos.bin",ios::binary|ios::in);

  for(int i=0;i<cantidad;i++){
    binario.read((char *)(imp+i),sizeof(Empleados));
  }

 cout<<"Los datos registrados en el archivo binario son los siguientes"<<endl;

 for(int i=0;i<cantidad;i++){
   cout<<"empleados numero: "<<i<<endl;
   cout<<"Nombre: "<<(imp+i)->nombre<<endl;
   cout<<"Apellido: "<<(imp+i)->apellido<<endl;
   cout<<"Id: "<<(imp+i)->codigo<<endl;
  cout<<"Celular: "<<(imp+i)->celular<<endl;
  cout<<endl<<endl;
 }
 binario.close();
}

void imprimirindice(int cantidad){
  int posicion[cantidad];

  ifstream indice;
  indice.open("indice.bin",ios::in|ios::binary);

  for(int i=0;i<cantidad;i++){
    indice.read((char *)&posicion[i],sizeof(int));
  }

  cout<<"Este es el archivo de indice"<<endl;
  for(int i=0;i<cantidad;i++){
    cout<<posicion[i]<<endl;
  }
  indice.close();
}

void archivotxt(int cantidad){

  ofstream abrirtxt;
  abrirtxt.open("datos.txt",ios::out);

  ifstream binario;
  binario.open("datos.bin",ios::binary|ios::in);

  Empleados *orden;
  orden= new Empleados[cantidad];

  Empleados* posicion;
  posicion = new Empleados [cantidad];


  if(binario.fail()){
    cout<<"No se pudo encontrar el archivo binario de lectura"<<endl;
  }else{
    for(int i=0;i<cantidad;i++){
      binario.read((char*)(orden+i),sizeof(Empleados));
    }

    posicion=orden;

    for(int i=0;i<cantidad-1;i++){
        for(int j=0;j<cantidad-1;j++){
          if(strcmp((posicion+j)->apellido,(posicion+j+1)->apellido) > 0) {
            Empleados aux = *(posicion+j);
            *(posicion+j) =*(posicion+j+1);
            *(posicion+j+1)=aux;
          }
        }
      }

      cout<<"Estos son los datos ordenados alfabeticamente por apellido "<<endl;

      for(int i=0;i<cantidad;i++){
        cout<<(posicion+i)->apellido;
        cout<<endl<<endl;
      }

  binario.close();
  for(int i=0;i<cantidad;i++){
      abrirtxt<<(posicion+i)->apellido<<","<<(posicion+i)->nombre<<","<<(posicion+i)->celular<<endl;
  }
   abrirtxt.close();
  }



  binario.close();
  abrirtxt.close();
}

int encontrarcantidad(string bin){

    Empleados temporal;

    ifstream binario;
    binario.open(bin.c_str(),ios::binary|ios::in);

    int n=0;

    while(!binario.eof()){
        n++;
        binario.read((char*)&(temporal),sizeof(Empleados));
  }
  return n-1;
}

void crearcarta(int cantidad){
    char *nombre, *apellido, *tok, *celular, linea[80], *token, linea2[200];
    int i = 0;
    char carta[] = "carta-";
    apellido = new char[20];
    celular = new char[10];
    nombre = new char[10];

    ifstream datostxt;
    datostxt.open("datos.txt", ios::in);
    while(cantidad != 0){
        ifstream formatotxt;
        ofstream cartatxt;
        strcpy(carta,"carta-");
        formatotxt.open("formato.txt", ios::in);
        if(!cartatxt){
            cout << "No se pudo crear el archivo carta "<<endl;
            exit(1);
        }
        if(!formatotxt || !datostxt){
            cout << "No se encontro el formato de la carta, por favor ingresar el archivo .txt en la carpeta manejada "<<endl;
            exit(1);
        }
        datostxt.getline(linea, 80, '\n');
        tok = strtok(linea, ",");
        strcpy(apellido, tok);
        tok = strtok(NULL, ",");
        strcpy(nombre, tok);
        tok = strtok(NULL, "\n");
        strcpy(celular, tok);
        strcat(carta, apellido);
        strcat(carta, nombre);
        strcat(carta, ".txt");
        cartatxt.open(carta,ios::out);
        while(!formatotxt.eof()){
            formatotxt.getline(linea2, 200, '\n');
            cartatxt << linea2 << '\n';
            formatotxt.getline(linea2, 200, '\n');
            cartatxt << nombre << " " << apellido << '\n';
            formatotxt.getline(linea2, 200, '\n');
            cartatxt << linea2 << '\n';
            formatotxt.getline(linea2, 200, '\n');
            cartatxt << linea2<< '\n';
            formatotxt.getline(linea2, 200, '\n');
            cartatxt << linea2<< '\n';
            formatotxt.getline(linea2, 200, '\n');
            token = strtok(linea2, "<");
            cartatxt << token;
            token = strtok(NULL, ">");
            token = strtok(NULL, "\n");
            cartatxt << celular << token << '\n';
            formatotxt.getline(linea2, 200, '\n');
            cartatxt << linea2<< '\n';
            formatotxt.getline(linea2, 200, '\n');
            cartatxt << linea2<< '\n';
            formatotxt.getline(linea2, 200, '\n');
            cartatxt << linea2<< '\n';
            formatotxt.getline(linea2, 200, '\n');
            cartatxt << linea2<< '\n';
        }
    cantidad--;
    cartatxt.close();
    formatotxt.close();
    i++;
    }

}

void anyadirempleado(int cantidad){

  int limite=cantidad+1;
  Empleados *lectura;
  lectura= new Empleados[limite];

  ifstream binario;
  binario.open("datos.bin",ios::in|ios::binary);
  if(binario.fail()){
    cout<<"No se encontro el archivo datos.bin"<<endl;
    exit(1);
  }else{

    for(int i=0;i<cantidad;i++){
      binario.read((char*)(lectura+i),sizeof(Empleados));
    }

    binario.close();


   ofstream binario;
   binario.open("datos.bin",ios::out|ios::binary);

    cout<<"Por favor digite los datos del empleado a añadir"<<endl;


    cout<<"ingrese el codigo del empleado "<<endl;
    cin>>(lectura+limite-1)->codigo;
    cin.ignore();
    cout<<"ingrese el apellido del empleado "<<endl;
    cin.getline((lectura+limite-1)->apellido,20);
    cout<<"ingrese el nombre del empleado "<<endl;
    cin.getline((lectura+limite-1)->nombre,20);
    cout<<"ingrese el numero de telefono del empleado"<<endl;
    cin>>(lectura+limite-1)->celular;

  //una vez tenidos los datos del nuevo empleado, se sobre escriben los datos del archivo binario ya creado

    for(int i=0;i<limite;i++){
      binario.write((char*)(lectura+i), sizeof(Empleados));
    }


  }

  imprimirbin(limite);
  binario.close();
}

void operadores(int cantidad){

  Empleados *lectura;
  lectura= new Empleados[cantidad+1];

    ifstream datbin;
    datbin.open("datos.bin",ios::in|ios::binary);
    ofstream movistar;
    movistar.open("movistar.bin", ios::out|ios::binary);
    ofstream claro;
    claro.open("claro.bin", ios::out|ios::binary);
    ofstream tigo;
    tigo.open("tigo.bin", ios::out|ios::binary);
    ofstream wom;
    wom.open("wom.bin", ios::out|ios::binary);
    for(int i=0;i<cantidad;i++){
      datbin.read((char*)(lectura+i),sizeof(Empleados));
    }
    for(int i=0;i<cantidad;i++){
        if((lectura+i)->celular<3250000000){
            movistar.write((char*)(lectura+i),sizeof(Empleados));
        }
        if((lectura+i)->celular<3500000000 && (lectura+i)->celular>3250000000){
            claro.write((char*)(lectura+i),sizeof(Empleados));
        }
        if((lectura+i)->celular<3750000000 && (lectura+i)->celular>3500000000){
            tigo.write((char*)(lectura+i),sizeof(Empleados));
        }
        if((lectura+i)->celular<4000000000 && (lectura+i)->celular>3750000000){
            wom.write((char*)(lectura+i),sizeof(Empleados));
        }
    }
  claro.close();
  movistar.close();
  tigo.close();
  wom.close();
}

void leeroperadores(){
  
  Empleados *ope;
  abrirope(ope, "Empleados con operador Movistar", "movistar.bin");
  abrirope(ope, "Empleados con operador Claro", "claro.bin");
  abrirope(ope, "Empleados con operador Tigo", "tigo.bin");
  abrirope(ope, "Empleados con operador Wom", "wom.bin");

}

void imprimirope(Empleados *ope, int cantidad, string titulo){
  if(cantidad>0)
    cout << titulo << endl;
  for(int i=0;i<cantidad;i++){
   cout<<"Nombre: "<<(ope+i)->nombre<<endl;
   cout<<"Apellido: "<<(ope+i)->apellido<<endl;
   cout<<"Id: "<<(ope+i)->codigo<<endl;
   cout<<"Celular: "<<(ope+i)->celular<<endl;
   cout<<endl<<endl;
  }
}

void abrirope(Empleados *ope, string titulo, string operador){
  int cantidad;
  cantidad = encontrarcantidad(operador);
  ope=new Empleados[cantidad];
  ifstream op;
  op.open(operador.c_str(), ios::in|ios::binary);
  for(int i=0;i<cantidad;i++)
    op.read((char *)(ope+i),sizeof(Empleados));
  imprimirope(ope, cantidad, titulo);
  op.close();
}