#ifndef ELEVADOR_H_INCLUDED
#define ELEVADOR_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

#define NFLOORS 10
#define CAPACIDADE 5
#define VEL_MAX 6 //m/s

//Definiçao de flags de direçao
#define DESCER       0
#define SUBIR        1
#define DONT_CARE    2
#define ELEV1_PARADO 3
#define ELEV2_PARADO 4
#define ELEV1_ANDA   5
#define ELEV2_ANDA   6
//Definiçao entrada ou saida de passageiros
#define SAIR   0
#define ENTRAR 1

//Definição de acoes por andar do elevador
#define NAO_PARA      0
#define PARA          1
#define PARA_SUBINDO  2
#define PARA_DESCENDO 3

//flag para atualizar matriz
#define PESSOA   0
#define ELEVADOR 1

//Definição de estados do elevador
#define PARADO   0
#define SUBINDO  1
#define DESCENDO 2

//Definição estados da porta
#define FECHADA 0
#define ABERTA  1

//Definição chegada de elevador
#define CHEGOU1 0
#define CHEGOU2 1
#define NENHUM  2
class control{

  public:

    uint8_t people_inside1, people_inside2, floor1, floor2, vel1, vel2;
    uint8_t estado1, estado2;
    uint8_t num_paradas_cima1;
    uint8_t num_paradas_baixo1;
    uint8_t num_paradas_cima2;
    uint8_t num_paradas_baixo2;

    void system_init(void);
    uint8_t calcula_proximo_andar(int dif1, int dif2);
    void checa_paradas(void);
    bool checa_capacidade(bool elevador);
    bool checa_velocidade(void);
    void atualiza_matriz_paradas(uint8_t floor, uint8_t direcao, bool pessoa_elevador);
    void atualiza_populacao(bool in_out, bool elev);
    uint8_t checa_elevador_proximo(void);
};
class elevator: public control{
    public:
	uint32_t actual_floor, people_inside, velocidade;
	bool porta;


    uint8_t matriz_paradas[NFLOORS+1];
	bool paradas_cima[NFLOORS+1], paradas_baixo[NFLOORS+1];

	void set_variables(void);
	void go_up(void);
	void go_down(void);
	void entra(void);
	void sai(void);
	unsigned int get(string);
	void open_door(void);
	void close_door(void);
	uint8_t acelera(uint8_t velocidade);
	uint8_t freia(uint8_t velocidade);
	void freio_de_seguranca(void);
};

class external_user : public control{
    public:
      bool actual_elevator;
      uint8_t actual_floor;

      void call_elevator(uint8_t actual_floor, uint8_t direcao);
      void enter(bool elevador);
};

class internal_user : public control{
    public:
      bool actual_elevator;
      uint8_t destination_floor;
      void set_destination(uint8_t floor);
      void out(bool elevador);
};

#endif // ELEVADOR_H_INCLUDED
