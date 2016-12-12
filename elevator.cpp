#include <iostream>
#include <string>
#include <cmath>
#include "elevador.h"
using namespace std;

    /***CLASS ELEVADOR***/

    /**INICIALIZACAO**/
  void elevator::set_variables(void){
    people_inside = 0;
    actual_floor = 0;
    velocidade = 0;
    for (int i = 0; i <= NFLOORS; i++){
        matriz_paradas[i] = NAO_PARA;
        paradas_baixo[i] = 0;
        paradas_cima[i] = 0;
    }
  }
  /**ENTRADA E SAIDA DE PASSAGEIROS**/
  void elevator::entra(void){
    if (people_inside >= CAPACIDADE){
        cout << "Este elevador esta lotado\n";
        people_inside = CAPACIDADE;
    }
    else people_inside++;
    }
  void elevator::sai(void){
    if (people_inside <= 0){
        cout << "Este elevador esta vazio\n";
        people_inside = 0;
    }
    else people_inside--;
    }/***FIM ENTRADA E SAIDA DE PASSAGEIROS***/

  /**MOVIMENAÇÃO DO ELEVADOR**/
  void elevator::go_up(void){
    if (actual_floor >= NFLOORS){
        cout << "Ultimo andar\n";
        actual_floor = NFLOORS;
    }
    else actual_floor++;
    }
  void elevator::go_down(void){
    if (actual_floor <= 0){
        cout << "Estamos no Terreo\n";
        actual_floor = 0;
    }
    else actual_floor--;
    }/**FIM MOVIMENTAÇÃO ELEVADOR**/

  /**AQUISIÇÃO DE VARIÁVEIS DO ELEVADOR**/
  unsigned int elevator::get(string atributo){
    if(atributo == "actual_floor"){
      //cout << actual_floor << "Andar\n";
      return actual_floor;
    }
    else if(atributo == "people_inside"){
      //cout << "Tem "<< people_inside << " pessoas neste elevador\n";
      return people_inside;
    }
    else if(atributo == "velocidade"){
      //cout << velocidade << "m/s\n";
      return velocidade;
    }
    else return 99;
  }/**FIM AQUISIÇÃO DE VARIÁVEIS DO ELEVADOR**/

  /***ABRIR E FECHAR PORTAS***/
  void elevator::open_door(void){
    elevator::porta = ABERTA;
    cout << "Porta Aberta\n";
  }
  void elevator::close_door(void){
    elevator::porta = FECHADA;
    cout << "Porta fechada\n";
  }
  /***FIM ABRIR E FECHAR PORTAS***/

  /***CONTROLE DE VELOCIDADE***/
  uint8_t elevator::acelera(uint8_t velocidade){
    velocidade++;
    if (velocidade >= VEL_MAX)
        velocidade = VEL_MAX;
    //cout << "A velocidade é"<< velocidade << "\n";
    return velocidade;
  }
  uint8_t elevator::freia(uint8_t velocidade){
    velocidade--;
    if (velocidade > VEL_MAX)
        velocidade = 0;
    //cout << "A velocidade é"<<velocidade<<"\n";
    return velocidade;
  }
  void elevator::freio_de_seguranca(void){
    while(velocidade != 0){
        velocidade--;
        for(int i = 0; i<1000; i++);
    }
  }
  /***FIM CONTROLE DE VELOCIDADE***/
  /****FIM DA CLASSE ELEVADOR****/

  elevator elevador1;
  elevator elevador2;

  /****CLASS INTERNAL USER****/
  void internal_user::set_destination(uint8_t floor){
    atualiza_matriz_paradas(floor, DONT_CARE, PESSOA);
  }

  void internal_user::out(bool elevador){
    atualiza_populacao(SAIR, elevador);
  }
  /****FIM DA CLASSE INTERNAL USER*****/

  /****CLASS EXTERNAL USER*****/

  /***FUNÇÃO PARA CHAMAR O ELEVADOR EM DETERMINADO ANDAR***/
  void external_user::call_elevator(uint8_t actual_floor, uint8_t direcao){
    atualiza_matriz_paradas(actual_floor, direcao, PESSOA);
  }/***FIM CHAMAR ELEVADOR***/

  /***FUNÇÃO PARA USUARIO ENTRAR NO ELEVADOR***/
  void external_user::enter(bool elevador){
    atualiza_populacao(ENTRAR, elevador);
  }/***FIM ENTRAR***/

  /*****FIM DA CLASSE EXTERNAL USER*****/

  /****CLASS CONTROL****/

  /***INICIALIZAÇÃO DE VARIÁVEIS***/
  void control::system_init(){
    elevador1.set_variables();
    elevador2.set_variables();
    people_inside1 = 0;
    people_inside2 = 0;
    floor1 = 0;
    floor2 = NFLOORS;
    estado1 = PARADO;
    estado2 = PARADO;
    vel1 = 0;
    vel2 = 0;
  }/***FIM INICIALIZAÇÃO***/

  /***CONTROLE DE PRÓXIMO ANDAR***/
  uint8_t control::calcula_proximo_andar(int dif1, int dif2){
  uint8_t valor_retorno = NENHUM;

    /**ELEVADOR 1**/
    if(dif1 < 0){
      /***Controle da velocidade***/
      if ((abs(dif1) <= vel1)&&(vel1 != 0))
        vel1 = elevador1.freia(vel1);
      else if (vel1 == 0)
        vel1 = 1;
      else vel1 = elevador1.acelera(vel1);
      elevador1.go_up();
      estado1 = SUBINDO;
    }
    else if(dif1 > 0){
      /***Controle da velocidade***/
      if ((abs(dif1) <= vel1)&&(vel1 != 0))
        vel1 = elevador1.freia(vel1);
      else if (vel1 == 0)
        vel1 = 1;
      else vel1 = elevador1.acelera(vel1);
      elevador1.go_down();
      estado1 = DESCENDO;
      }
    else if(dif1 == 0){
      vel1 = elevador1.freia(vel1);
      if(((estado1==DESCENDO)&&(num_paradas_baixo1 == 0))||((estado1==SUBINDO)&&(num_paradas_cima1 == 0))){
          estado1 = PARADO;
        }
      valor_retorno = CHEGOU1;
    }/**FIM ELEVADOR1**/

    /**ELEVADOR2**/
    if(dif2 < 0){
      /***Controle da velocidade***/
      if ((abs(dif2) <= vel2)&&(vel2 != 0))
        vel2 = elevador2.freia(vel2);
      else if (vel2 == 0)
        vel2 = 1;
      else vel2 = elevador2.acelera(vel2);
      elevador2.go_up();
      estado2 = SUBINDO;
      }
      else if(dif2 > 0){
      /***Controle da velocidade***/
        if ((abs(dif2) <= vel2)&&(vel2 != 0))
          vel2 = elevador2.freia(vel2);
        else if (vel2 == 0)
          vel2 = 1;
        else vel2 = elevador2.acelera(vel2);
        elevador2.go_down();
        estado2 = DESCENDO;
      }
      else if(dif2 == 0){
        vel2 = elevador2.freia(vel2);
        if(((estado2==DESCENDO)&&(num_paradas_baixo2 == 0))||((estado2==SUBINDO)&&(num_paradas_cima2 == 0))){
          estado2 = PARADO;
        }
        if(valor_retorno == NENHUM)
          valor_retorno = CHEGOU2;
      }
      return valor_retorno;
  }/***FIM CONTROLE DE PRÓXIMO ANDAR***/

  /***CONTROLE DE ATUALIZAÇÃO DE PARADAS PARA CIMA E PARA BAIXO DE CADA ELEVADOR***/
  void control::checa_paradas(void){

    num_paradas_cima1 = 0;
    num_paradas_baixo1 = 0;
    num_paradas_cima2 = 0;
    num_paradas_baixo2 = 0;
    for(int i = 0; i<=NFLOORS; i++){
      if((elevador1.matriz_paradas[i] == PARA_SUBINDO)){
        elevador1.paradas_cima[i] = 1;
        num_paradas_cima1++;
      }
      else if((elevador1.matriz_paradas[i] == PARA_DESCENDO)){
        elevador1.paradas_baixo[i] = 1;
        num_paradas_baixo1++;
      }
      else if(elevador1.matriz_paradas[i] == PARA){
        elevador1.paradas_cima[i] = 1;
        num_paradas_cima1++;
        elevador1.paradas_baixo[i] = 1;
        num_paradas_baixo1++;
      }
      else if(elevador1.matriz_paradas[i] == NAO_PARA){
        elevador1.paradas_cima[i] = 0;
        elevador1.paradas_baixo[i] = 0;
      }
      if((elevador2.matriz_paradas[i] == PARA_SUBINDO)){
        elevador2.paradas_cima[i] = 1;
        num_paradas_cima2++;
      }
      else if((elevador2.matriz_paradas[i] == PARA_SUBINDO)){
        elevador2.paradas_baixo[i] = 1;
        num_paradas_baixo2++;
      }
      else if(elevador2.matriz_paradas[i] == PARA){
        elevador2.paradas_cima[i] = 1;
        num_paradas_cima2++;
        elevador2.paradas_baixo[i] = 1;
        num_paradas_baixo2++;
      }
      else if(elevador2.matriz_paradas[i] == NAO_PARA){
        elevador2.paradas_cima[i] = 0;
        elevador2.paradas_baixo[i] = 0;
      }
    }
  }/***FIM CONTROLE DE PARADAS***/

    /***CONTROLE DE CAPACIDADE MÁXIMA EXEDIDA***/
  bool control::checa_capacidade(bool elevador){
    people_inside1 = elevador1.get("people_inside");
    people_inside2 = elevador2.get("peopple_inside");
    bool capacidade = 1;
    if (elevador == 0){
      if(people_inside1==CAPACIDADE)
         capacidade = 0;
    }
    else if(elevador == 1){
      if(people_inside2==CAPACIDADE)
          capacidade = 0;
    }
    return capacidade;
  }/***FIM CONTROLE DE CAPACIDADE***/

  /***VERIFICAÇÃO DA VELOCIDADE PARA ANALISAR SE ULTRAPASSOU A VELOCIDADE MAXIMA***/
  bool control::checa_velocidade(void){
    vel1 = elevador1.get("velocidade");
    vel2 = elevador2.get("velocidade");
    if((vel1>VEL_MAX)||(vel2>VEL_MAX))
        return 0;
    else return 1;
  }/***FIM VERIFICAÇÃO DA VELOCIDADE***/

  /***ATUALIZAÇAO DAS MATRIZES DE PARADAS DOS ELEVADORES***/
  void control::atualiza_matriz_paradas(uint8_t floor, uint8_t direcao, bool pessoa_elevador){
    if(pessoa_elevador == ELEVADOR){
      if(direcao == ELEV1_PARADO)
        elevador2.matriz_paradas[floor] = NAO_PARA;
      else if(direcao == ELEV2_PARADO)
        elevador1.matriz_paradas[floor] = NAO_PARA;
      else if(direcao == ELEV1_ANDA)
        elevador1.matriz_paradas[floor] = NAO_PARA;
      else if(direcao == ELEV2_ANDA)
        elevador2.matriz_paradas[floor] = NAO_PARA;
    }
    else if(pessoa_elevador == PESSOA){
      if (direcao == DONT_CARE){
        elevador1.matriz_paradas[floor] = PARA;
        elevador2.matriz_paradas[floor] = PARA;
      }
      else if(direcao == DESCER){
        elevador1.matriz_paradas[floor] = PARA_DESCENDO;
        elevador2.matriz_paradas[floor] = PARA_DESCENDO;
      }
      else if(direcao == SUBIR){
        elevador1.matriz_paradas[floor] = PARA_SUBINDO;
        elevador2.matriz_paradas[floor] = PARA_SUBINDO;
      }
    }
  }/***FIM ATUALIZAÇÃO DAS MATRIZES DE PARADAS***/

    /***ATUALIZA POPULAÇÃO***/
  void control::atualiza_populacao(bool in_out, bool elev){
    if (elev == 1){
      if(in_out == ENTRAR){
        elevador2.entra();
        people_inside2 = elevador2.get("people_inside");
      }
      else{
        elevador2.sai();
        people_inside2 = elevador2.get("people_inside");
      }
    }
    else{
      if(in_out == ENTRAR){
        elevador1.entra();
        people_inside1 = elevador1.get("people_inside");
      }
      else{
        elevador1.sai();
        people_inside1 = elevador1.get("people_inside");
      }
    }
  } /***FIM ATUALIZA POPULAÇÃO***/

    /***CHECA PARADA MAIS PROXIMA E ENVIA DIFERENCA PARA CALCULO DO PROXIMO ANDAR***/
  uint8_t control::checa_elevador_proximo(void){
    floor1 = elevador1.get("actual_floor");
    floor2 = elevador2.get("actual_floor");
    int diferenca1 = NFLOORS;
    int diferenca2 = NFLOORS;
    diferenca1 = NFLOORS;
    diferenca2 = NFLOORS;

    /**CALCULA DIFERENÇA 1**/
    for(int i=0; i<NFLOORS; i++){
      if (estado1 == PARADO){
        if((elevador1.paradas_cima[i] == 1)||(elevador1.paradas_baixo[i]==1)){
          if(abs(floor1-i) < abs(diferenca1))
            diferenca1 = floor1-i;
        }
      }
      else if(estado1 == SUBINDO){
        if(elevador1.paradas_cima[i] == 1){
          if(abs(floor1-i) < abs(diferenca1))
            diferenca1 = floor1 - i;
        }
      }
      else if(estado1 == DESCENDO){
        if(elevador1.paradas_baixo[i] == 1){
          if(abs(floor1-i) < abs(diferenca1))
            diferenca1 = floor1 - i;
        }
      }/**FIM CALCULA DIFERENÇA 1**/

      /**CALCULA DIFERENÇA 2**/
      if (estado2 == PARADO){
        if((elevador2.paradas_cima[i] == 1)||(elevador2.paradas_baixo[i] == 1)){
          if(abs(floor2-i) < abs(diferenca2)){
            diferenca2 = floor2-i;
          }
        }
      }
      if (estado2 == SUBINDO){
        if(elevador2.paradas_cima[i] == 1){
          if(abs(floor2-i) < abs(diferenca2)){
            diferenca2 = floor2 - i;
          }
        }
      }
      else if(estado2 == DESCENDO){
        if(elevador2.paradas_baixo[i] == 1){
          if(abs(floor2-i) < abs(diferenca2)){
            diferenca2 = floor2 - i;
          }
        }
      }/**FIM CALCULA DIFERENÇA 2**/

    }/**DISTANCIAS CALCULADAS**/

    return calcula_proximo_andar(diferenca1, diferenca2);

  }/***FIM CHECA ELEVADOR MAIS PROXIMO***/
