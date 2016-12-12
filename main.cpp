#include <iostream>
#include <string>
#include <cmath>
#include "elevador.h"
#include "elevator.cpp"
using namespace std;


/*Código desenvolvido pelos alunos Bruno Neckel e Pedro Henrique Fornari
 *Desenvolvimento de controle para elevadores de prédios com número de andares pré definido
 *O código abaixo mostra o comportamento sequencial do controle dos dois elevadores
 *selecionando o elevador mais próximo do usuario quando os dois elevadores estão em movimento
 *as funções utilizadas estão melhor explicadas no arquivo elevator.cpp,
 *onde está a implementação de cada função.
 *definições de constantes podem ser encontradas no arquivo elevador.h, assim como os protótipos
 *de cada função
 *As funções tem nomes intuitivos para facilitar o entendimento
 */

int main(){
  control controle_principal;
  /***USUARIO 1***/
  external_user Eusuario1;          //USUARIO EXTERNO1
  Eusuario1.actual_floor = 0;       //ENCONTRA-SE NO TERREO
  internal_user Iusuario1;          //USUARIO INTERNO1
  Iusuario1.destination_floor = 5;  //DESEJA IR AO ANDAR 5

  /***USUARIO 2***/
  external_user Eusuario2;          //USUARIO EXTERNO2
  Eusuario2.actual_floor = 3;       //ENCONTRA-SE NO ANDAR 3
  internal_user Iusuario2;          //USUARIO INTERNO2
  Iusuario2.destination_floor = 7;  //DESEJA IR AO ANDAR 7

  /***USUARIO 3***/
  external_user Eusuario3;          //USUARIO EXTERNO3
  Eusuario3.actual_floor = 4;       //ENCONTRA-SE NO ANDAR 4
  internal_user Iusuario3;          //USUARIO INTERNO3
  Iusuario3.destination_floor = 0;  //DESEJA IR AO TERREO

  int delay = 0;                    //VARIAVEL PARA CRIAR ATRASO ENTRE OS ELEVADORES
  controle_principal.system_init(); //INICIALIZAÇÃO DO CONTROLE E DE VARIÁVEIS

  /***USUARIOS DIFERENTES CHAMAM O ELEVADOR DE DIFERENTES ANDARES***/
  Eusuario1.call_elevator(Eusuario1.actual_floor, SUBIR);
  Eusuario2.call_elevator(Eusuario2.actual_floor, SUBIR);
  Eusuario3.call_elevator(Eusuario3.actual_floor, DESCER);
  /***COM AS MATRIZES ATUALIZADAS PARTIMOS PARA A MOVIMENTAÇÃO DO ELEVADOR***/
  int cont_parada;
  bool flag = 1;
  while(flag){

    controle_principal.checa_paradas();                         //CONTROLE VERIFICA AS PARADAS NECESSÁRIAS
    cont_parada = controle_principal.checa_elevador_proximo();  //FUNCAO QUE MOVIMENTA ELEVADOR SEGUNDO UM CALCULO DE OTIMIZAÇÃO
    /***TESTES SÃO FEITOS PARA VERIFICAR SE O ELEVADOR SE ENCONTRA EM UM ANDAR ONDE DEVE PARAR***/
    if(cont_parada == CHEGOU1){
      if(Eusuario1.actual_floor == elevador1.get("actual_floor")){
        controle_principal.atualiza_matriz_paradas(Eusuario1.actual_floor, ELEV1_PARADO, ELEVADOR);
        if(controle_principal.checa_capacidade(0) == 1){
          if(delay==2){
            cout<<"ELEVADOR1 ";
            elevador1.open_door();
            cout<<"USUARIO1 NO ELEVADOR1\n";
            Eusuario1.enter(0);
            controle_principal.atualiza_matriz_paradas(Eusuario1.actual_floor, ELEV1_ANDA, ELEVADOR);
            Eusuario1.actual_floor = 99;
            cout<<"ELEVADOR1 ";
            elevador1.close_door();
            Iusuario1.actual_elevator = 0;
            Iusuario1.set_destination(Iusuario1.destination_floor);
            delay = 0;
          }
        }
      }
      else if(Eusuario2.actual_floor == elevador1.get("actual_floor")){
        controle_principal.atualiza_matriz_paradas(Eusuario2.actual_floor, ELEV1_PARADO, ELEVADOR);
        if(controle_principal.checa_capacidade(0) == 1){
          if(delay == 2){
            cout<<"ELEVADOR1 ";
            elevador1.open_door();
            cout<<"USUARIO2 NO ELEVADOR1\n";
            Eusuario2.enter(0);
            controle_principal.atualiza_matriz_paradas(Eusuario2.actual_floor, ELEV1_ANDA, ELEVADOR);
            Eusuario2.actual_floor = 99;
            cout<<"ELEVADOR1 ";
            elevador1.close_door();
            Iusuario2.actual_elevator = 0;
            Iusuario2.set_destination(Iusuario2.destination_floor);
            delay = 0;
          }
        }
      }
      else if(Eusuario3.actual_floor == elevador1.get("actual_floor")){
        controle_principal.atualiza_matriz_paradas(Eusuario3.actual_floor, ELEV1_PARADO, ELEVADOR);
        if(controle_principal.checa_capacidade(0) == 1){
          if(delay == 2){
            cout<<"ELEVADOR1 ";
            elevador1.open_door();
            cout<<"USUARIO3 NO ELEVADOR1\n";
            Eusuario3.enter(0);
            controle_principal.atualiza_matriz_paradas(Eusuario3.actual_floor, ELEV1_ANDA, ELEVADOR);
            Eusuario3.actual_floor = 99;
            cout<<"ELEVADOR1 ";
            elevador1.close_door();
            Iusuario3.actual_elevator = 0;
            Iusuario3.set_destination(Iusuario3.destination_floor);
            delay = 0;
          }
        }
      }
      else if((Iusuario1.actual_elevator==0)&&(Iusuario1.destination_floor == elevador1.get("actual_floor"))){
        controle_principal.atualiza_matriz_paradas(Iusuario1.destination_floor, ELEV1_PARADO, ELEVADOR);
        if(delay == 2){
          cout<<"ELEVADOR1 ";
          elevador1.open_door();
          cout<<"USUARIO1 SAI DO ELEVADOR1\n";
          Iusuario1.out(0);
          controle_principal.atualiza_matriz_paradas(Iusuario1.destination_floor, ELEV1_ANDA, ELEVADOR);
          Iusuario1.destination_floor = 99;
          cout<<"ELEVADOR1 ";
          elevador1.close_door();
          delay = 0;
        }
      }
      else if((Iusuario2.actual_elevator==0)&&(Iusuario2.destination_floor == elevador1.get("actual_floor"))){
        controle_principal.atualiza_matriz_paradas(Iusuario2.destination_floor, ELEV1_PARADO, ELEVADOR);
        if(delay == 2){
          cout<<"ELEVADOR1 ";
          elevador1.open_door();
          Iusuario2.out(0);
          controle_principal.atualiza_matriz_paradas(Iusuario2.destination_floor, ELEV1_ANDA, ELEVADOR);
          Iusuario2.destination_floor = 99;
          cout<<"ELEVADOR1 ";
          elevador1.close_door();
          delay = 0;
        }
      }
      else if((Iusuario3.actual_elevator==0)&&(Iusuario3.destination_floor == elevador1.get("actual_floor"))){
        controle_principal.atualiza_matriz_paradas(Iusuario3.destination_floor, ELEV1_PARADO, ELEVADOR);
        if(delay == 2){
          cout<<"ELEVADOR1 ";
          elevador1.open_door();
          cout<<"USUARIO3 SAI DO ELEVADOR1\n";
          Iusuario3.out(0);
          controle_principal.atualiza_matriz_paradas(Iusuario3.destination_floor, ELEV1_ANDA, ELEVADOR);
          Iusuario3.destination_floor = 99;
          cout<<"ELEVADOR1 ";
          elevador1.close_door();
          delay = 0;
          flag = 0;
        }
      }
      delay++;
    }

    else if(cont_parada == CHEGOU2){
      if(Eusuario1.actual_floor == elevador2.get("actual_floor")){
        controle_principal.atualiza_matriz_paradas(Eusuario1.actual_floor, ELEV2_PARADO, ELEVADOR);
        if(controle_principal.checa_capacidade(1) == 1){
          if(delay == 2){
            cout<<"ELEVADOR2 ";
            elevador2.open_door();
            cout<<"USUARIO1 NO ELEVADOR2\n";
            Eusuario1.enter(1);
            controle_principal.atualiza_matriz_paradas(Eusuario1.actual_floor, ELEV2_ANDA, ELEVADOR);
            Eusuario1.actual_floor = 99;
            cout<<"ELEVADOR2 ";
            elevador2.close_door();
            Iusuario1.actual_elevator = 1;
            Iusuario1.set_destination(Iusuario1.destination_floor);
            delay = 0;
          }
        }
      }
      else if(Eusuario2.actual_floor == elevador2.get("actual_floor")){
        controle_principal.atualiza_matriz_paradas(Eusuario2.actual_floor, ELEV2_PARADO, ELEVADOR);
        if(controle_principal.checa_capacidade(1) == 1){
          if(delay ==2){
            cout<<"ELEVADOR2 ";
            elevador2.open_door();
            cout<<"USUARIO2 NO ELEVADOR2\n";
            controle_principal.atualiza_matriz_paradas(Eusuario2.actual_floor, ELEV2_ANDA, ELEVADOR);
            Eusuario2.enter(1);
            Eusuario2.actual_floor = 99;
            cout<<"ELEVADOR2 ";
            elevador2.close_door();
            Iusuario2.actual_elevator = 1;
            Iusuario2.set_destination(Iusuario2.destination_floor);
            delay = 0;
          }
        }
      }
      else if(Eusuario3.actual_floor == elevador2.get("actual_floor")){
        controle_principal.atualiza_matriz_paradas(Eusuario3.actual_floor, ELEV2_PARADO, ELEVADOR);
        if(controle_principal.checa_capacidade(1) == 1){
          if(delay == 2){
            cout<<"ELEVADOR2 ";
            elevador2.open_door();
            cout<<"USUARIO3 NO ELEVADOR2\n";
            Eusuario3.enter(1);
            controle_principal.atualiza_matriz_paradas(Eusuario3.actual_floor, ELEV2_ANDA, ELEVADOR);
            Eusuario3.actual_floor = 99;
            cout<<"ELEVADOR2 ";
            elevador2.close_door();
            Iusuario3.actual_elevator = 1;
            Iusuario3.set_destination(Iusuario3.destination_floor);
            delay = 0;
          }
        }
      }
      else if((Iusuario1.actual_elevator==1)&&(Iusuario1.destination_floor == elevador2.get("actual_floor"))){
        controle_principal.atualiza_matriz_paradas(Iusuario1.destination_floor, ELEV2_PARADO, ELEVADOR);
        if(delay == 2){
          cout<<"ELEVADOR2 ";
          elevador2.open_door();
          cout<<"USUARIO1 SAI DO ELEVADOR2\n";
          Iusuario1.out(1);
          controle_principal.atualiza_matriz_paradas(Iusuario1.destination_floor, ELEV2_ANDA, ELEVADOR);
          Iusuario1.destination_floor = 99;
          cout<<"ELEVADOR2 ";
          elevador2.close_door();
          delay = 0;
        }
      }
      else if((Iusuario2.actual_elevator==1)&&(Iusuario2.destination_floor == elevador2.get("actual_floor"))){
        controle_principal.atualiza_matriz_paradas(Iusuario2.destination_floor, ELEV2_PARADO, ELEVADOR);
        if(delay == 2){
          cout<<"ELEVADOR2 ";
          elevador2.open_door();
          cout<<"USUARIO2 SAI DO ELEVADOR2\n";
          Iusuario2.out(1);
          controle_principal.atualiza_matriz_paradas(Iusuario2.destination_floor, ELEV2_ANDA, ELEVADOR);
          Iusuario2.destination_floor = 99;
          cout<<"ELEVADOR2 ";
          elevador1.close_door();
          delay = 0;
        }
      }
      else if((Iusuario3.actual_elevator==0)&&(Iusuario3.destination_floor == elevador2.get("actual_floor"))){
        controle_principal.atualiza_matriz_paradas(Iusuario3.destination_floor, ELEV2_PARADO, ELEVADOR);
        if(delay == 2){
          cout<<"ELEVADOR2 ";
          elevador2.open_door();
          cout<<"USUARIO3 SAI DO ELEVADOR2\n";
          Iusuario3.out(1);
          controle_principal.atualiza_matriz_paradas(Iusuario3.destination_floor, ELEV2_ANDA, ELEVADOR);
          Iusuario3.destination_floor = 99;
          cout<<"ELEVADOR2 ";
          elevador2.close_door();
          delay = 0;
          flag = 0;
        }
      }
      delay++;
    }


    /***IMPRESSÃO DE ANDAR ATUAL E VELOCIDADE DE CADA ELEVADOR, PARA FACILITAR VISUALIZAÇÃO***/
    cout<<"elevador1 no andar "<< int(controle_principal.floor1);
    cout<<" com velocidade de "<< int(controle_principal.vel1) <<" metros por segundo\n";
    cout<<"elevador2 no andar "<<int(controle_principal.floor2);
    cout<<" com velocidade de " <<int(controle_principal.vel2)<<" metros por segundo\n";
  }
  return 1;
}
