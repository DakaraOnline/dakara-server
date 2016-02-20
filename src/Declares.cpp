/******************************************************************************
    Copyright (C) 2002-2015 Argentum Online & Dakara Online Developers

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#include "stdafx.h"

#include "Declares.h"

std::shared_ptr<clsAntiMassClon> aClon;
std::set<WorldPos> TrashCollector;

const int MAXSPAWNATTEMPS = 60;
const int INFINITE_LOOPS = /* FANCY EXPRESSION */-1;
const int FXSANGRE = 14;

/* '' */
/* ' The color of chats over head of dead characters. */
const int CHAT_COLOR_DEAD_CHAR = 0xC0C0C0;

/* '' */
/* ' The color of yells made by any kind of game administrator. */
const int CHAT_COLOR_GM_YELL = 0xF82FF;

/* '' */
/* ' Coordinates for normal sounds (not 3D, like rain) */
const int NO_3D_SOUND = 0;

const int iFragataFantasmal = 87;
const int iFragataReal = 190;
const int iFragataCaos = 189;
const int iBarca = 84;
const int iGalera = 85;
const int iGaleon = 86;

/* ' Embarcaciones ciudas */
const int iBarcaCiuda = 395;
const int iBarcaCiudaAtacable = 552;
const int iGaleraCiuda = 397;
const int iGaleraCiudaAtacable = 560;
const int iGaleonCiuda = 399;
const int iGaleonCiudaAtacable = 556;

/* ' Embarcaciones reales */
const int iBarcaReal = 550;
const int iBarcaRealAtacable = 553;
const int iGaleraReal = 558;
const int iGaleraRealAtacable = 561;
const int iGaleonReal = 554;
const int iGaleonRealAtacable = 557;

/* ' Embarcaciones pk */
const int iBarcaPk = 396;
const int iGaleraPk = 398;
const int iGaleonPk = 400;

/* ' Embarcaciones caos */
const int iBarcaCaos = 551;
const int iGaleraCaos = 559;
const int iGaleonCaos = 555;

const int LimiteNewbie = 12;

/* 'Cabecera de los con */

struct tCabecera MiCabecera;

/* 'Barrin 3/10/03 */
/* 'Cambiado a 2 segundos el 30/11/07 */
const int TIEMPO_INICIOMEDITAR = 2000;

const int NingunEscudo = 2;
const int NingunCasco = 2;
const int NingunArma = 2;

const int EspadaMataDragonesIndex = 402;
const int LAUDMAGICO = 696;
const int FLAUTAMAGICA = 208;

const int LAUDELFICO = 1049;
const int FLAUTAELFICA = 1050;

const int APOCALIPSIS_SPELL_INDEX = 25;
const int DESCARGA_SPELL_INDEX = 23;

const int SLOTS_POR_FILA = 5;

const int PROB_ACUCHILLAR = 20;
const float DANO_ACUCHILLAR = 0.2;

const int MAXMASCOTASENTRENADOR = 7;

const int TIEMPO_CARCEL_PIQUETE = 10;

/* '' */
/* ' TRIGGERS */
/* ' */
/* ' @param NADA nada */
/* ' @param BAJOTECHO bajo techo */
/* ' @param trigger_2 ??? */
/* ' @param POSINVALIDA los npcs no pueden pisar tiles con este trigger */
/* ' @param ZONASEGURA no se puede robar o pelear desde este trigger */
/* ' @param ANTIPIQUETE */
/* ' @param ZONAPELEA al pelear en este trigger no se caen las cosas y no cambia el estado de ciuda o crimi */
/* ' */

/* '' */
/* ' constantes para el trigger 6 */
/* ' */
/* ' @see eTrigger */
/* ' @param TRIGGER6_PERMITE TRIGGER6_PERMITE */
/* ' @param TRIGGER6_PROHIBE TRIGGER6_PROHIBE */
/* ' @param TRIGGER6_AUSENTE El trigger no aparece */
/* ' */

/* 'TODO : Reemplazar por un enum */
const std::string Bosque = "BOSQUE";
const std::string Nieve = "NIEVE";
const std::string Desierto = "DESIERTO";
const std::string Ciudad = "CIUDAD";
const std::string Campo = "CAMPO";
const std::string Dungeon = "DUNGEON";

/* ' <<<<<< Targets >>>>>> */

/* ' <<<<<< Acciona sobre >>>>>> */

const int MAXUSERHECHIZOS = 35;

/* ' TODO: Y ESTO ? LO CONOCE GD ? */
const int EsfuerzoTalarGeneral = 4;
const int EsfuerzoTalarLenador = 2;

const int EsfuerzoPescarPescador = 1;
const int EsfuerzoPescarGeneral = 3;

const int EsfuerzoExcavarMinero = 2;
const int EsfuerzoExcavarGeneral = 5;

const int FX_TELEPORT_INDEX = 1;

const float PORCENTAJE_MATERIALES_UPGRADE = 0.85;

/* ' La utilidad de esto es casi nula, sólo se revisa si fue a la cabeza... */

const int Guardias = 6;

const int MAX_ORO_EDIT = 5000000;
const int MAX_VIDA_EDIT = 30000;

const std::string STANDARD_BOUNTY_HUNTER_MESSAGE =
		"Se te ha otorgado un premio por ayudar al proyecto reportando bugs, el mismo está disponible en tu bóveda.";
const std::string TAG_USER_INVISIBLE = "[INVISIBLE]";
const std::string TAG_CONSULT_MODE = "[CONSULTA]";

const int MAXREP = 6000000;
const int MAXORO = 90000000;
const int MAXEXP = 99999999;

const int MAXUSERMATADOS = 65000;

const int MAXATRIBUTOS = 40;
const int MINATRIBUTOS = 6;

const int LingoteHierro = 386;
const int LingotePlata = 387;
const int LingoteOro = 388;
const int Lena = 58;
const int LenaElfica = 1006;

const int MAXNPCS = 10000;
const int MAXCHARS = 10000;

const int HACHA_LENADOR = 127;
const int HACHA_LENA_ELFICA = 1005;
const int PIQUETE_MINERO = 187;

const int HACHA_LENADOR_NEWBIE = 561;
const int PIQUETE_MINERO_NEWBIE = 562;
const int CANA_PESCA_NEWBIE = 563;
const int SERRUCHO_CARPINTERO_NEWBIE = 564;
const int MARTILLO_HERRERO_NEWBIE = 565;

const int DAGA = 15;
const int FOGATA_APAG = 136;
const int FOGATA = 63;
const int ORO_MINA = 194;
const int PLATA_MINA = 193;
const int HIERRO_MINA = 192;
const int MARTILLO_HERRERO = 389;
const int SERRUCHO_CARPINTERO = 198;
const int ObjArboles = 4;
const int RED_PESCA = 543;
const int CANA_PESCA = 138;

const int MIN_APUNALAR = 10;

/* '********** CONSTANTANTES *********** */

/* '' */
/* ' Cantidad de skills */
const int NUMSKILLS = 20;

/* '' */
/* ' Cantidad de Atributos */
const int NUMATRIBUTOS = 5;

/* '' */
/* ' Cantidad de Clases */
const int NUMCLASES = 12;

/* '' */
/* ' Cantidad de Razas */
const int NUMRAZAS = 5;

/* '' */
/* ' Valor maximo de cada skill */
const int MAXSKILLPOINTS = 100;

/* '' */
/* ' Cantidad de Ciudades */
const int NUMCIUDADES = 6;

/* '' */
/* 'Direccion */
/* ' */
/* ' @param NORTH Norte */
/* ' @param EAST Este */
/* ' @param SOUTH Sur */
/* ' @param WEST Oeste */
/* ' */

/* '' */
/* ' Cantidad maxima de mascotas */
const int MAXMASCOTAS = 3;

/* '%%%%%%%%%% CONSTANTES DE INDICES %%%%%%%%%%%%%%% */
const int vlASALTO = 100;
const int vlASESINO = 1000;
const int vlCAZADOR = 5;
const int vlNoble = 5;
const int vlLadron = 25;
const int vlProleta = 2;

/* '%%%%%%%%%% CONSTANTES DE INDICES %%%%%%%%%%%%%%% */
const int iCuerpoMuerto = 8;
const int iCabezaMuerto = 500;

const int iORO = 12;
const int Pescado = 139;

const int NUM_PECES = 4;
vb6::array<int> ListaPeces;

/* '%%%%%%%%%% CONSTANTES DE INDICES %%%%%%%%%%%%%%% */

const int FundirMetal = eSkill_FundirMetal;

/* 'HP adicionales cuando sube de nivel */
const int AdicionalHPGuerrero = 2;
/* 'HP adicionales cuando sube de nivel */
const int AdicionalHPCazador = 1;

const int AumentoSTDef = 15;
const int AumentoStBandido = /* FANCY EXPRESSION */AumentoSTDef + 3;
const int AumentoSTLadron = /* FANCY EXPRESSION */AumentoSTDef + 3;
const int AumentoSTMago = /* FANCY EXPRESSION */AumentoSTDef - 1;
const int AumentoSTTrabajador = /* FANCY EXPRESSION */AumentoSTDef + 25;

/* 'Tamano del mapa */
const int XMaxMapSize = 100;
const int XMinMapSize = 1;
const int YMaxMapSize = 100;
const int YMinMapSize = 1;

/* 'Tamano del tileset */
const int TileSizeX = 32;
const int TileSizeY = 32;

/* 'Tamano en Tiles de la pantalla de visualizacion */
const int XWindow = 17;
const int YWindow = 13;

/* 'Sonidos */
const int SND_SWING = 2;
const int SND_TALAR = 13;
const int SND_PESCAR = 14;
const int SND_MINERO = 15;
const int SND_WARP = 3;
const int SND_PUERTA = 5;
const int SND_NIVEL = 6;

const int SND_USERMUERTE = 11;
const int SND_IMPACTO = 10;
const int SND_IMPACTO2 = 12;
const int SND_LENADOR = 13;
const int SND_FOGATA = 14;
const int SND_AVE = 21;
const int SND_AVE2 = 22;
const int SND_AVE3 = 34;
const int SND_GRILLO = 28;
const int SND_GRILLO2 = 29;
const int SND_SACARARMA = 25;
const int SND_ESCUDO = 37;
const int MARTILLOHERRERO = 41;
const int LABUROCARPINTERO = 42;
const int SND_BEBER = 46;

/* '' */
/* ' Cantidad maxima de objetos por slot de inventario */
const int MAX_INVENTORY_OBJS = 10000;

/* '' */
/* ' Cantidad de "slots" en el inventario con mochila */
const int MAX_INVENTORY_SLOTS = 30;

/* '' */
/* ' Cantidad de "slots" en el inventario sin mochila */
const int MAX_NORMAL_INVENTORY_SLOTS = 20;

/* '' */
/* ' Constante para indicar que se esta usando ORO */
const int FLAGORO = /* FANCY EXPRESSION */MAX_INVENTORY_SLOTS + 1;

/* ' CATEGORIAS PRINCIPALES */

/* 'Texto */
const std::string FONTTYPE_TALK = "~255~255~255~0~0";
const std::string FONTTYPE_FIGHT = "~255~0~0~1~0";
const std::string FONTTYPE_WARNING = "~32~51~223~1~1";
const std::string FONTTYPE_INFO = "~65~190~156~0~0";
const std::string FONTTYPE_INFOBOLD = "~65~190~156~1~0";
const std::string FONTTYPE_EJECUCION = "~130~130~130~1~0";
const std::string FONTTYPE_PARTY = "~255~180~255~0~0";
const std::string FONTTYPE_VENENO = "~0~255~0~0~0";
const std::string FONTTYPE_GUILD = "~255~255~255~1~0";
const std::string FONTTYPE_SERVER = "~0~185~0~0~0";
const std::string FONTTYPE_GUILDMSG = "~228~199~27~0~0";
const std::string FONTTYPE_CONSEJO = "~130~130~255~1~0";
const std::string FONTTYPE_CONSEJOCAOS = "~255~60~00~1~0";
const std::string FONTTYPE_CONSEJOVesA = "~0~200~255~1~0";
const std::string FONTTYPE_CONSEJOCAOSVesA = "~255~50~0~1~0";
const std::string FONTTYPE_CENTINELA = "~0~255~0~1~0";

/* 'Estadisticas */
const int STAT_MAXELV = 255;
const int STAT_MAXHP = 999;
const int STAT_MAXSTA = 999;
const int STAT_MAXMAN = 9999;
const int STAT_MAXHIT_UNDER36 = 99;
const int STAT_MAXHIT_OVER36 = 999;
const int STAT_MAXDEF = 99;

const int ELU_SKILL_INICIAL = 200;
const int EXP_ACIERTO_SKILL = 50;
const int EXP_FALLO_SKILL = 20;

/* ' ************************************************************** */
/* ' ************************************************************** */
/* ' ************************ TIPOS ******************************* */
/* ' ************************************************************** */
/* ' ************************************************************** */

/* 'Datos de user o npc */

/* 'Tipos de objetos */

/* '[Pablo ToxicWaste] */

/* '[/Pablo ToxicWaste] */

/* '[KEVIN] */
/* 'Banco Objs */
const int MAX_BANCOINVENTORY_SLOTS = 40;
/* '[/KEVIN] */

/* '[KEVIN] */
/* '[/KEVIN] */

/* ' Determina el color del nick */

/* '******* */
/* 'FOROS * */
/* '******* */

/* ' Tipos de mensajes */

/* ' Indica los privilegios para visualizar los diferentes foros */

/* ' Indica el tipo de foro */

/* ' Limite de posts */
const int MAX_STICKY_POST = 10;
const int MAX_GENERAL_POST = 35;

/* ' Estructura contenedora de mensajes */
/* ' Public Type tForo */
/* '    StickyTitle(1 To MAX_STICKY_POST) As String */
/* '    StickyPost(1 To MAX_STICKY_POST) As String */
/* '    GeneralTitle(1 To MAX_GENERAL_POST) As String */
/* '    GeneralPost(1 To MAX_GENERAL_POST) As String */
/* ' End Type */

/* '********************************************************* */
/* '********************************************************* */
/* '********************************************************* */
/* '********************************************************* */
/* '******* T I P O S   D E    U S U A R I O S ************** */
/* '********************************************************* */
/* '********************************************************* */
/* '********************************************************* */
/* '********************************************************* */

/* 'Fama del usuario */

/* 'Estadisticas de los usuarios */

/* 'Flags */

/* # IF SeguridadAlkon THEN */
/* # END IF */

/* # IF SeguridadAlkon THEN */
/* # END IF */

/* 'Cosas faccionarias. */

/* 'Tipo de los Usuarios */

/* # IF SeguridadAlkon THEN */
/* # END IF */

/* # IF ConUpTime THEN */
/* # END IF */

/* '********************************************************* */
/* '********************************************************* */
/* '********************************************************* */
/* '********************************************************* */
/* '**  T I P O S   D E    N P C S ************************** */
/* '********************************************************* */
/* '********************************************************* */
/* '********************************************************* */
/* '********************************************************* */

/* ' New type for holding the pathfinding info */

/* ' New type for holding the pathfinding info */

const int MAX_NPC_DROPS = 5;

/* '********************************************************** */
/* '********************************************************** */
/* '******************** Tipos del mapa ********************** */
/* '********************************************************** */
/* '********************************************************** */
/* 'Tile */

/* 'Info del mapa */

/* '********** V A R I A B L E S     P U B L I C A S *********** */

bool SERVERONLINE;
std::string ULTIMAVERSION;
/* ' TODO: Se usa esta variable ? */
bool BackUp;

vb6::array<std::string> ListaRazas;
vb6::array<std::string> SkillsNames;
vb6::array<std::string> ListaClases;
vb6::array<std::string> ListaAtributos;

int RECORDusuarios;

/* '' */
/* 'Bordes del mapa */
int MinXBorder;
int MaxXBorder;
int MinYBorder;
int MaxYBorder;

/* '' */
/* 'Numero de usuarios actual */
int NumUsers;
int LastUser;
int LastChar;
int NumChars;
int LastNPC;
int NumNPCs;
int NumFX;
int NumMaps;
int NumObjDatas;
int NumeroHechizos;
int AllowMultiLogins;
int LimiteConexionesPorIp;
int IdleLimit;
int MaxUsers;
int HideMe;
std::string LastBackup;
std::string Minutos;
bool haciendoBK;
int PuedeCrearPersonajes;
int ServerSoloGMs;
int NumRecords;
float HappyHour;
bool HappyHourActivated;
vb6::array<float> HappyHourDays;

int RegistroListaBlancaEmails;
std::set<std::string> RegistroEmailsHabilitados;

/* '' */
/* 'Esta activada la verificacion MD5 ? */
int MD5ClientesActivado;

bool EnPausa;
bool EnTesting;

/* '*****************ARRAYS PUBLICOS************************* */
/* 'USUARIOS */
vb6::array<struct User> UserList;
/* 'NPCS */
vb6::array<struct npc> Npclist;
vb6::array<vb6::array<vb6::array<struct MapBlock> > > MapData;
vb6::array<struct MapInfo> MapInfo;
vb6::array<struct tHechizo> Hechizos;
vb6::array<int> CharList;
vb6::array<struct ObjData> ObjData;
//vb6::array<struct FXdata> FX;
vb6::array<struct tCriaturasEntrenador> SpawnList;
vb6::array<struct LevelSkill> LevelSkill;
vb6::array<std::string> ForbidenNames;
vb6::array<int> ArmasHerrero;
vb6::array<int> ArmadurasHerrero;
vb6::array<int> ObjCarpintero;
std::vector<std::string> MD5s;
std::set<std::string> BanIps;
vb6::array<std::shared_ptr<clsParty>> Parties;
vb6::array<struct ModClase> ModClase;
vb6::array<struct ModRaza> ModRaza;
vb6::array<double> ModVida;
vb6::array<int> DistribucionEnteraVida;
vb6::array<int> DistribucionSemienteraVida;
vb6::array<struct WorldPos> Ciudades;
vb6::array<struct HomeDistance> distanceToCities;
vb6::array<struct tRecord> Records;
/* '********************************************************* */

struct WorldPos Nix;
struct WorldPos Ullathorpe;
struct WorldPos Banderbill;
struct WorldPos Lindos;
struct WorldPos Arghal;
struct WorldPos Arkhein;
struct WorldPos Nemahuak;

struct WorldPos Prision;
struct WorldPos Libertad;

//std::shared_ptr<cCola> Ayuda;
//std::shared_ptr<cCola> Denuncias;
std::deque<std::string> Ayuda;
std::deque<std::string> Denuncias;
std::shared_ptr<ConsultasPopulares> ConsultaPopular;
std::shared_ptr<SoundMapInfo> SonidosMapas;

const int MATRIX_INITIAL_MAP = 1;

const int GOHOME_PENALTY = 5;
const int GM_MAP = 49;

const int TELEP_OBJ_INDEX = 1012;

const int HUMANO_H_PRIMER_CABEZA = 1;
/* 'En verdad es hasta la 51, pero como son muchas estas las dejamos no seleccionables */
const int HUMANO_H_ULTIMA_CABEZA = 40;

const int ELFO_H_PRIMER_CABEZA = 101;
const int ELFO_H_ULTIMA_CABEZA = 122;

const int DROW_H_PRIMER_CABEZA = 201;
const int DROW_H_ULTIMA_CABEZA = 221;

const int ENANO_H_PRIMER_CABEZA = 301;
const int ENANO_H_ULTIMA_CABEZA = 319;

const int GNOMO_H_PRIMER_CABEZA = 401;
const int GNOMO_H_ULTIMA_CABEZA = 416;
/* '************************************************** */
const int HUMANO_M_PRIMER_CABEZA = 70;
const int HUMANO_M_ULTIMA_CABEZA = 89;

const int ELFO_M_PRIMER_CABEZA = 170;
const int ELFO_M_ULTIMA_CABEZA = 188;

const int DROW_M_PRIMER_CABEZA = 270;
const int DROW_M_ULTIMA_CABEZA = 288;

const int ENANO_M_PRIMER_CABEZA = 370;
const int ENANO_M_ULTIMA_CABEZA = 384;

const int GNOMO_M_PRIMER_CABEZA = 470;
const int GNOMO_M_ULTIMA_CABEZA = 484;

/* ' Por ahora la dejo constante.. SI se quisiera extender la propiedad de paralziar, se podria hacer */
/* ' una nueva variable en el dat. */
const int GUANTE_HURTO = 873;

const int ESPADA_VIKINGA = 123;
/* ''''''' */
/* '' Pretorianos */
/* ''''''' */
/* FIXME: PRETORIANOS */
// vb6::array<std::shared_ptr<clsClanPretoriano>> ClanPretoriano;

const int MAX_DENOUNCES = 20;
const int MAX_PENAS = 1000;
const int MAX_SPECIAL_USERS = 1000;
const int MAX_MAPS = 1000;
const int MAX_EXPRESIONES = 10000;
const int MAX_SONIDOS = 1000;
const int MAX_DAT_ITEMS = 100000;
const int MAX_CRIATURAS_ENTRENADOR = 10000;
const int MAX_HELP_LINES = 10000;

/* 'Mensajes de los NPCs enlistadores (Nobles): */
const std::string MENSAJE_REY_CAOS =
		"¿Esperabas pasar desapercibido, intruso? Los servidores del Demonio no son bienvenidos, ¡Guardias, a él!";
const std::string MENSAJE_REY_CRIMINAL_NOENLISTABLE =
		"Tus pecados son grandes, pero aún así puedes redimirte. El pasado deja huellas, pero aún puedes limpiar tu alma.";
const std::string MENSAJE_REY_CRIMINAL_ENLISTABLE =
		"Limpia tu reputación y paga por los delitos cometidos. Un miembro de la Armada Real debe tener un comportamiento ejemplar.";

const std::string MENSAJE_DEMONIO_REAL =
		"Lacayo de Tancredo, ve y dile a tu gente que nadie pisará estas tierras si no se arrodilla ante mi.";
const std::string MENSAJE_DEMONIO_CIUDADANO_NOENLISTABLE =
		"Tu indecisión te ha condenado a una vida sin sentido, aún tienes elección... Pero ten mucho cuidado, mis hordas nunca descansan.";
const std::string MENSAJE_DEMONIO_CIUDADANO_ENLISTABLE =
		"Siento el miedo por tus venas. Deja de ser escoria y únete a mis filas, sabrás que es el mejor camino.";

std::shared_ptr<clsIniManager> Administradores;

const int MIN_AMOUNT_LOG = 1000;
const int MIN_VALUE_LOG = 50000;
const int MIN_GOLD_AMOUNT_LOG = 10000;

/* 'TODO:Esto hay que volarlo, es temporal! */
//std::string GUILDPATH;
//std::string GUILDINFOFILE;

std::string DakaraBasePath;
