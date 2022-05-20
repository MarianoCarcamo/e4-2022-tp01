#include <ensamblador.h>
#include <unity.h>
#include <timer_systick.h>

void setUp(void){}
void tearDown(void){}

static void copiaMemoria_debe_copiar_cero_bytes(void);
static void copiaMemoria_debe_copiar_un_byte(void);
static void copiaMemoria_debe_copiar_media_palabra(void);
static void copiaMemoria_debe_copiar_una_palabra(void);
static void copiaMemoria_debe_copiar_una_palabra_mal_alineada(void);
static void copiaCadena_debe_copiar_una_cadena(void);
static void copiaCadena_debe_respetar_el_espacio_de_destino(void);
static void mayusculaEnLugar_debe_pasar_a_mayuscula_una_cadena(void);
static void mayusculaEnLugar_debe_respetar_la_longitud_maxima(void);
static void minusculaEnLugar_debe_pasar_a_minuscula_una_cadena(void);
static void minusculaEnLugar_debe_respetar_la_longitud_maxima(void);


/* Ejecución de las pruebas */

int main(void)
{
    TimerSysTick_init();
    TimerSysTick_esperaMilisegundos(500);
    UNITY_BEGIN();
    
    RUN_TEST(copiaMemoria_debe_copiar_cero_bytes);
    RUN_TEST(copiaMemoria_debe_copiar_un_byte);
    RUN_TEST(copiaMemoria_debe_copiar_media_palabra);
    RUN_TEST(copiaMemoria_debe_copiar_una_palabra);
    RUN_TEST(copiaMemoria_debe_copiar_una_palabra_mal_alineada);
    
    RUN_TEST(copiaCadena_debe_copiar_una_cadena);
    RUN_TEST(copiaCadena_debe_respetar_el_espacio_de_destino); //mirar terminador nulo y R2 
    
    RUN_TEST(mayusculaEnLugar_debe_pasar_a_mayuscula_una_cadena);
    RUN_TEST(mayusculaEnLugar_debe_respetar_la_longitud_maxima);
    
    RUN_TEST(minusculaEnLugar_debe_pasar_a_minuscula_una_cadena);
    RUN_TEST(minusculaEnLugar_debe_respetar_la_longitud_maxima);
    return UNITY_END();   
}

/* Pruebas para copiaMemoria */

enum {XA = 0x55U,XB = 0xAAU};

static void copiaMemoria_debe_copiar_cero_bytes(void)
{
    const uint8_t origen[4] = {XA};
    const uint8_t esperado[4] = {XB,XB,XB,XB};
    uint8_t destino[4] = {XB,XB,XB,XB};
    copiaMemoria(origen,destino,0);
    TEST_ASSERT_EQUAL_MEMORY(esperado,destino,4);
}

static void copiaMemoria_debe_copiar_un_byte(void)
{
    const uint8_t origen[4] = {XA};
    const uint8_t esperado[4] = {XA,XB,XB,XB};
    uint8_t destino[4] = {XB,XB,XB,XB};

    copiaMemoria(origen,destino,1);
    TEST_ASSERT_EQUAL_MEMORY(esperado,destino,4);
}

static void copiaMemoria_debe_copiar_media_palabra(void)
{
    const uint8_t origen[4] = {XA,XA};
    const uint8_t esperado[4] = {XA,XA,XB,XB};
    uint8_t destino[4] = {XB,XB,XB,XB};

    copiaMemoria(origen,destino,2);
    TEST_ASSERT_EQUAL_MEMORY(esperado,destino,4);
}

static void copiaMemoria_debe_copiar_una_palabra(void)
{
    const uint8_t origen[8] = {XA,XA,XA,XA};
    const uint8_t esperado[8] = {XA,XA,XA,XA,XB,XB,XB,XB};
    uint8_t destino[8] = {XB,XB,XB,XB,XB,XB,XB,XB};

    copiaMemoria(origen,destino,4);
    TEST_ASSERT_EQUAL_MEMORY(esperado,destino,8);
}

static void copiaMemoria_debe_copiar_una_palabra_mal_alineada(void)
{
    const uint8_t origen[8] = {0,XA,XA,XA,XA};
    const uint8_t esperado[8] = {XB,XB,XB,XA,XA,XA,XA,XB};
    uint8_t destino[8] = {XB,XB,XB,XB,XB,XB,XB,XB};

    copiaMemoria(origen+1,destino+3,4);
    TEST_ASSERT_EQUAL_MEMORY(esperado,destino,8);
}

/* Pruebas para copiaCadena */

static void copiaCadena_debe_copiar_una_cadena(void)
{
    const char origen[] =   "Cadena";
    char destino[17]    =   "0123456789ABCDEF";
    const char esperado[17]="Cadena" "\0" "789ABCDEF";
    copiaCadena(origen,destino,sizeof(destino));
    TEST_ASSERT_EQUAL_CHAR_ARRAY(esperado,destino,17);
}

static void copiaCadena_debe_respetar_el_espacio_de_destino(void)
{
    const char origen[] =   "Cadena";
    char destino[17]    =   "0123456789ABCDEF";
    const char esperado[17]="Cad" "\0" "456789ABCDEF";
    copiaCadena(origen,destino,4);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(esperado,destino,17);
}

/* Pruebas para mayusculaEnLugar */

static void mayusculaEnLugar_debe_pasar_a_mayuscula_una_cadena(void)
{
    char cadena[] = "CaDeNa123";
    const char esperado[]="CADENA123";
    mayusculaEnLugar(cadena,sizeof(cadena));
    TEST_ASSERT_EQUAL_CHAR_ARRAY(esperado,cadena,sizeof(esperado));
}

static void mayusculaEnLugar_debe_respetar_la_longitud_maxima(void)
{
    char cadena[] = "cadena123";
    const char esperado[]="CADena123";
    mayusculaEnLugar(cadena,3);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(esperado,cadena,sizeof(esperado));
}

/* Pruebas para minusculaEnLugar */

static void minusculaEnLugar_debe_pasar_a_minuscula_una_cadena(void)
{
    char cadena[] = "CaDeNa123";
    const char esperado[]="cadena123";
    minusculaEnLugar(cadena,sizeof(cadena));
    TEST_ASSERT_EQUAL_CHAR_ARRAY(esperado,cadena,sizeof(esperado));
}

static void minusculaEnLugar_debe_respetar_la_longitud_maxima(void)
{
    char cadena[] = "CADENA123";
    const char esperado[]="cadENA123";
    minusculaEnLugar(cadena,3);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(esperado,cadena,sizeof(esperado));
}
