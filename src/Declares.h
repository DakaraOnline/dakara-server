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

#ifndef DECLARACIONES_H
#define DECLARACIONES_H

#include <boost/date_time/posix_time/ptime.hpp>
#include <deque>
#include <set>
#include <vector>
#include <memory>
#include <string>
#include <map>

#include "AntiMassClon.h"
#include "Areas.h"
#include "ByteQueue.h"
#include "ConsultasPopulares.h"
#include "enums.h"
#include "IniManager.h"
#include "MapSoundManager.h"
#include "Party.h"
#include "vb6compat.h"
#include "ComercioUsuario.h"


namespace dakara {
	class Socket;
}

extern std::shared_ptr<clsAntiMassClon> aClon;
extern std::set<WorldPos> TrashCollector;

extern const int MAXSPAWNATTEMPS;
extern const int INFINITE_LOOPS;
extern const int FXSANGRE;

/* '' */
/* ' The color of chats over head of dead characters. */
extern const int CHAT_COLOR_DEAD_CHAR;

/* '' */
/* ' The color of yells made by any kind of game administrator. */
extern const int CHAT_COLOR_GM_YELL;

/* '' */
/* ' Coordinates for normal sounds (not 3D, like rain) */
extern const int NO_3D_SOUND;

extern const int iFragataFantasmal;
extern const int iFragataReal;
extern const int iFragataCaos;
extern const int iBarca;
extern const int iGalera;
extern const int iGaleon;

/* ' Embarcaciones ciudas */
extern const int iBarcaCiuda;
extern const int iBarcaCiudaAtacable;
extern const int iGaleraCiuda;
extern const int iGaleraCiudaAtacable;
extern const int iGaleonCiuda;
extern const int iGaleonCiudaAtacable;

/* ' Embarcaciones reales */
extern const int iBarcaReal;
extern const int iBarcaRealAtacable;
extern const int iGaleraReal;
extern const int iGaleraRealAtacable;
extern const int iGaleonReal;
extern const int iGaleonRealAtacable;

/* ' Embarcaciones pk */
extern const int iBarcaPk;
extern const int iGaleraPk;
extern const int iGaleonPk;

/* ' Embarcaciones caos */
extern const int iBarcaCaos;
extern const int iGaleraCaos;
extern const int iGaleonCaos;

extern const int LimiteNewbie;

/* 'Cabecera de los con */
struct tCabecera {
	std::string desc;
	int crc = 0;
	int MagicWord = 0;
};

extern struct tCabecera MiCabecera;

/* 'Barrin 3/10/03 */
/* 'Cambiado a 2 segundos el 30/11/07 */
extern const int TIEMPO_INICIOMEDITAR;

extern const int NingunEscudo;
extern const int NingunCasco;
extern const int NingunArma;

extern const int EspadaMataDragonesIndex;
extern const int LAUDMAGICO;
extern const int FLAUTAMAGICA;

extern const int LAUDELFICO;
extern const int FLAUTAELFICA;

extern const int APOCALIPSIS_SPELL_INDEX;
extern const int DESCARGA_SPELL_INDEX;

extern const int SLOTS_POR_FILA;

extern const int PROB_ACUCHILLAR;
extern const float DANO_ACUCHILLAR;

extern const int MAXMASCOTASENTRENADOR;

extern const int TIEMPO_CARCEL_PIQUETE;

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
extern const std::string Bosque;
extern const std::string Nieve;
extern const std::string Desierto;
extern const std::string Ciudad;
extern const std::string Campo;
extern const std::string Dungeon;

/* ' <<<<<< Targets >>>>>> */

/* ' <<<<<< Acciona sobre >>>>>> */

extern const int MAXUSERHECHIZOS;

/* ' TODO: Y ESTO ? LO CONOCE GD ? */
extern const int EsfuerzoTalarGeneral;
extern const int EsfuerzoTalarLenador;

extern const int EsfuerzoPescarPescador;
extern const int EsfuerzoPescarGeneral;

extern const int EsfuerzoExcavarMinero;
extern const int EsfuerzoExcavarGeneral;

extern const int FX_TELEPORT_INDEX;

extern const float PORCENTAJE_MATERIALES_UPGRADE;

/* ' La utilidad de esto es casi nula, sólo se revisa si fue a la cabeza... */

extern const int Guardias;

extern const int MAX_ORO_EDIT;
extern const int MAX_VIDA_EDIT;

extern const std::string STANDARD_BOUNTY_HUNTER_MESSAGE;
extern const std::string TAG_USER_INVISIBLE;
extern const std::string TAG_CONSULT_MODE;

extern const int MAXREP;
extern const int MAXORO;
extern const int MAXEXP;

extern const int MAXUSERMATADOS;

extern const int MAXATRIBUTOS;
extern const int MINATRIBUTOS;

extern const int LingoteHierro;
extern const int LingotePlata;
extern const int LingoteOro;
extern const int Lena;
extern const int LenaElfica;

extern const int MAXNPCS;
extern const int MAXCHARS;

extern const int HACHA_LENADOR;
extern const int HACHA_LENA_ELFICA;
extern const int PIQUETE_MINERO;

extern const int HACHA_LENADOR_NEWBIE;
extern const int PIQUETE_MINERO_NEWBIE;
extern const int CANA_PESCA_NEWBIE;
extern const int SERRUCHO_CARPINTERO_NEWBIE;
extern const int MARTILLO_HERRERO_NEWBIE;

extern const int DAGA;
extern const int FOGATA_APAG;
extern const int FOGATA;
extern const int ORO_MINA;
extern const int PLATA_MINA;
extern const int HIERRO_MINA;
extern const int MARTILLO_HERRERO;
extern const int SERRUCHO_CARPINTERO;
extern const int ObjArboles;
extern const int RED_PESCA;
extern const int CANA_PESCA;

extern const int MIN_APUNALAR;

/* '********** CONSTANTANTES *********** */

/* '' */
/* ' Cantidad de skills */
extern const int NUMSKILLS;

/* '' */
/* ' Cantidad de Atributos */
extern const int NUMATRIBUTOS;

/* '' */
/* ' Cantidad de Clases */
extern const int NUMCLASES;

/* '' */
/* ' Cantidad de Razas */
extern const int NUMRAZAS;

/* '' */
/* ' Valor maximo de cada skill */
extern const int MAXSKILLPOINTS;

/* '' */
/* ' Cantidad de Ciudades */
extern const int NUMCIUDADES;

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
extern const int MAXMASCOTAS;

/* '%%%%%%%%%% CONSTANTES DE INDICES %%%%%%%%%%%%%%% */
extern const int vlASALTO;
extern const int vlASESINO;
extern const int vlCAZADOR;
extern const int vlNoble;
extern const int vlLadron;
extern const int vlProleta;

/* '%%%%%%%%%% CONSTANTES DE INDICES %%%%%%%%%%%%%%% */
extern const int iCuerpoMuerto;
extern const int iCabezaMuerto;

extern const int iORO;
extern const int Pescado;

extern const int NUM_PECES;
extern vb6::array<int> ListaPeces;

/* '%%%%%%%%%% CONSTANTES DE INDICES %%%%%%%%%%%%%%% */

extern const int FundirMetal;

/* 'HP adicionales cuando sube de nivel */
extern const int AdicionalHPGuerrero;
/* 'HP adicionales cuando sube de nivel */
extern const int AdicionalHPCazador;

extern const int AumentoSTDef;
extern const int AumentoStBandido;
extern const int AumentoSTLadron;
extern const int AumentoSTMago;
extern const int AumentoSTTrabajador;

/* 'Tamano del mapa */
extern const int XMaxMapSize;
extern const int XMinMapSize;
extern const int YMaxMapSize;
extern const int YMinMapSize;

/* 'Tamano del tileset */
extern const int TileSizeX;
extern const int TileSizeY;

/* 'Tamano en Tiles de la pantalla de visualizacion */
extern const int XWindow;
extern const int YWindow;

/* 'Sonidos */
extern const int SND_SWING;
extern const int SND_TALAR;
extern const int SND_PESCAR;
extern const int SND_MINERO;
extern const int SND_WARP;
extern const int SND_PUERTA;
extern const int SND_NIVEL;

extern const int SND_USERMUERTE;
extern const int SND_IMPACTO;
extern const int SND_IMPACTO2;
extern const int SND_LENADOR;
extern const int SND_FOGATA;
extern const int SND_AVE;
extern const int SND_AVE2;
extern const int SND_AVE3;
extern const int SND_GRILLO;
extern const int SND_GRILLO2;
extern const int SND_SACARARMA;
extern const int SND_ESCUDO;
extern const int MARTILLOHERRERO;
extern const int LABUROCARPINTERO;
extern const int SND_BEBER;

/* '' */
/* ' Cantidad maxima de objetos por slot de inventario */
extern const int MAX_INVENTORY_OBJS;

/* '' */
/* ' Cantidad de "slots" en el inventario con mochila */
extern const int MAX_INVENTORY_SLOTS;

/* '' */
/* ' Cantidad de "slots" en el inventario sin mochila */
extern const int MAX_NORMAL_INVENTORY_SLOTS;

/* '' */
/* ' Constante para indicar que se esta usando ORO */
extern const int FLAGORO;

/* ' CATEGORIAS PRINCIPALES */

/* 'Texto */
extern const std::string FONTTYPE_TALK;
extern const std::string FONTTYPE_FIGHT;
extern const std::string FONTTYPE_WARNING;
extern const std::string FONTTYPE_INFO;
extern const std::string FONTTYPE_INFOBOLD;
extern const std::string FONTTYPE_EJECUCION;
extern const std::string FONTTYPE_PARTY;
extern const std::string FONTTYPE_VENENO;
extern const std::string FONTTYPE_GUILD;
extern const std::string FONTTYPE_SERVER;
extern const std::string FONTTYPE_GUILDMSG;
extern const std::string FONTTYPE_CONSEJO;
extern const std::string FONTTYPE_CONSEJOCAOS;
extern const std::string FONTTYPE_CONSEJOVesA;
extern const std::string FONTTYPE_CONSEJOCAOSVesA;
extern const std::string FONTTYPE_CENTINELA;

/* 'Estadisticas */
extern const int STAT_MAXELV;
extern const int STAT_MAXHP;
extern const int STAT_MAXSTA;
extern const int STAT_MAXMAN;
extern const int STAT_MAXHIT_UNDER36;
extern const int STAT_MAXHIT_OVER36;
extern const int STAT_MAXDEF;

extern const int ELU_SKILL_INICIAL;
extern const int EXP_ACIERTO_SKILL;
extern const int EXP_FALLO_SKILL;

/* ' ************************************************************** */
/* ' ************************************************************** */
/* ' ************************ TIPOS ******************************* */
/* ' ************************************************************** */
/* ' ************************************************************** */

struct tObservacion {
	std::string Creador;
	boost::posix_time::ptime Fecha{};

	std::string Detalles;
};

struct tRecord {
	std::string Usuario;
	std::string Motivo;
	std::string Creador;
	boost::posix_time::ptime Fecha;

	int NumObs{};
	vb6::array<struct tObservacion> Obs;
};

struct tHechizo {
	std::string Nombre;
	std::string desc;
	std::string PalabrasMagicas;

	std::string HechizeroMsg;
	std::string TargetMsg;
	std::string PropioMsg;

	/* '    Resis As Byte */

	TipoHechizo Tipo;

	int WAV{};
	int FXgrh{};
	int loops{};

	int SubeHP{};
	int MinHp{};
	int MaxHp{};

	int SubeMana{};
	int MiMana{};
	int MaMana{};

	int SubeSta{};
	int MinSta{};
	int MaxSta{};

	int SubeHam{};
	int MinHam{};
	int MaxHam{};

	int SubeSed{};
	int MinSed{};
	int MaxSed{};

	int SubeAgilidad{};
	int MinAgilidad{};
	int MaxAgilidad{};

	int SubeFuerza{};
	int MinFuerza{};
	int MaxFuerza{};

	int SubeCarisma{};
	int MinCarisma{};
	int MaxCarisma{};

	int Invisibilidad{};
	int Paraliza{};
	int Inmoviliza{};
	int RemoverParalisis{};
	int RemoverEstupidez{};
	int CuraVeneno{};
	int Envenena{};
	int Maldicion{};
	int RemoverMaldicion{};
	int Bendicion{};
	int Estupidez{};
	int Ceguera{};
	int Revivir{};
	int Morph{};
	int Mimetiza{};
	int RemueveInvisibilidadParcial{};

	int Warp{};
	int Invoca{};
	int NumNpc{};
	int cant{};

	/* '    Materializa As Byte */
	/* '    ItemIndex As Byte */

	int MinSkill{};
	int ManaRequerido{};

	/* 'Barrin 29/9/03 */
	int StaRequerido{};

	TargetType Target;

	int NeedStaff{};
	bool StaffAffected{};
};

struct LevelSkill {
	int LevelValue{};
};

struct UserOBJ {
	UserOBJ() : ObjIndex(0), Amount(0), Equipped(0) {}

	int ObjIndex;
	int Amount;
	int Equipped;
};

struct Inventario {
	Inventario() {
		Object.redim(1, MAX_INVENTORY_SLOTS);
		NroItems = 0;
	}

	vb6::array<struct UserOBJ> Object;
	int WeaponEqpObjIndex{};
	int WeaponEqpSlot{};
	int ArmourEqpObjIndex{};
	int ArmourEqpSlot{};
	int EscudoEqpObjIndex{};
	int EscudoEqpSlot{};
	int CascoEqpObjIndex{};
	int CascoEqpSlot{};
	int MunicionEqpObjIndex{};
	int MunicionEqpSlot{};
	int AnilloEqpObjIndex{};
	int AnilloEqpSlot{};
	int BarcoObjIndex{};
	int BarcoSlot{};
	int MochilaEqpObjIndex{};
	int MochilaEqpSlot{};
	int NroItems;
};

struct tPartyData {
	int PIndex{};
	/* 'La exp. en el server se cuenta con Doubles */
	double RemXP{};
	/* 'Para las invitaciones */
	int TargetUser{};
};

struct Position {
	Position() : X(0), Y(0) {}
	Position(int x, int y) : X(x), Y(y) {}

	int X = 0;
	int Y = 0;

	bool operator<(const Position& other) const {
		// return (X < other.X) || (X == other.X && Y < other.Y);
		return std::make_tuple(X, Y) < std::make_tuple(other.X, other.Y);
	}

	bool operator==(const Position& other) const {
		return std::make_tuple(X, Y) == std::make_tuple(other.X, other.Y);
	}

	bool operator!=(const Position& other) const {
		return std::make_tuple(X, Y) != std::make_tuple(other.X, other.Y);
	}
};

struct WorldPos {
	WorldPos() {}
	WorldPos(const Position& p) : Map(0), X(p.X), Y(p.Y) {}

	int Map = 0;
	int X = 0;
	int Y = 0;

	bool operator <(const WorldPos& other) const {
		if (Map < other.Map)
			return true;
		else if (Map == other.Map && X < other.X)
			return true;
		else if (Map == other.Map && X == other.X && Y < other.Y)
			return true;
		return false;
	}
};

struct FXdata {
	std::string Nombre;
	int GrhIndex = 0;
	int Delay = 0;
};

/* 'Datos de user o npc */
struct Char {
	int CharIndex = 0;
	int Head = 0;
	int body = 0;

	int WeaponAnim = 0;
	int ShieldAnim = 0;
	int CascoAnim = 0;

	int FX = 0;
	int loops = 0;

	eHeading heading = eHeading_None;
};

/* 'Tipos de objetos */
struct ObjData {
	ObjData() {
		ClaseProhibida.redim(1, NUMCLASES);
	}

	/* 'Nombre del obj */
	std::string Name;

	/* 'Tipo enum que determina cuales son las caract del obj */
	eOBJType OBJType = eOBJType_Null;

	/* ' Indice del grafico que representa el obj */
	int GrhIndex = 0;
	int GrhSecundario = 0;

	/* 'Solo contenedores */
	int MaxItems = 0;
	struct Inventario Conte;
	int Apunala = 0;
	int Acuchilla = 0;

	int HechizoIndex = 0;

	std::string ForoID;

	/* ' Minimo puntos de vida */
	int MinHp = 0;
	/* ' Maximo puntos de vida */
	int MaxHp = 0;

	int MineralIndex = 0;
	int LingoteInex = 0;

	int proyectil = 0;
	int Municion = 0;

	int Crucial = 0;
	int Newbie = 0;

	/* 'Puntos de Stamina que da */
	/* ' Minimo puntos de stamina */
	int MinSta = 0;

	/* 'Pociones */
	int TipoPocion = 0;
	int MaxModificador = 0;
	int MinModificador = 0;
	int DuracionEfecto = 0;
	int MinSkill = 0;
	int LingoteIndex = 0;

	/* 'Minimo golpe */
	int MinHIT = 0;
	/* 'Maximo golpe */
	int MaxHIT = 0;

	int MinHam = 0;
	int MinSed = 0;

	int def = 0;
	/* ' Armaduras */
	int MinDef = 0;
	/* ' Armaduras */
	int MaxDef = 0;

	/* 'Indice del grafico del ropaje */
	int Ropaje = 0;

	/* ' Apunta a una anim de armas */
	int WeaponAnim = 0;
	int WeaponRazaEnanaAnim = 0;
	/* ' Apunta a una anim de escudo */
	int ShieldAnim = 0;
	int CascoAnim = 0;

	/* ' Precio */
	int Valor = 0;

	int Cerrada = 0;
	int Llave = 0;
	/* 'si clave=llave la puerta se abre o cierra */
	int clave = 0;

	/* ' Para teleps: El radio para calcular el random de la pos destino */
	int Radio = 0;

	/* 'Tipo de Mochila (1 la chica, 2 la grande) */
	int MochilaType = 0;

	/* ' Indica si es un guante o no. */
	int Guante = 0;

	int IndexAbierta = 0;
	int IndexCerrada = 0;
	int IndexCerradaLlave = 0;

	int RazaEnana = 0;
	int RazaDrow = 0;
	int RazaElfa = 0;
	int RazaGnoma = 0;
	int RazaHumana = 0;

	int Mujer = 0;
	int Hombre = 0;

	int Envenena = 0;
	int Paraliza = 0;

	int Agarrable = 0;

	int LingH = 0;
	int LingO = 0;
	int LingP = 0;
	int Madera = 0;
	int MaderaElfica = 0;

	int SkHerreria = 0;
	int SkCarpinteria = 0;

	std::string texto;

	/* 'Clases que no tienen permitido usar este obj */
	vb6::array<eClass> ClaseProhibida;

	int Snd1 = 0;
	int Snd2 = 0;
	int Snd3 = 0;

	int Real = 0;
	int Caos = 0;

	int NoSeCae = 0;
	int NoSeTira = 0;
	int NoRobable = 0;
	int NoComerciable = 0;
	int Intransferible = 0;

	int StaffPower = 0;
	int StaffDamageBonus = 0;
	int DefensaMagicaMax = 0;
	int DefensaMagicaMin = 0;
	int Refuerzo = 0;

	int ImpideParalizar = 0;
	int ImpideInmobilizar = 0;
	int ImpideAturdir = 0;
	int ImpideCegar = 0;

	/* 'es un objeto que queremos loguear? Pablo (ToxicWaste) 07/09/07 */
	int Log = 0;
	/* 'es un objeto que esta prohibido loguear? */
	int NoLog = 0;

	int Upgrade = 0;
};

struct Obj {
	int ObjIndex = 0;
	int Amount = 0;
};

/* '[Pablo ToxicWaste] */
struct ModClase {
	double Evasion = 0.0;
	double AtaqueArmas = 0.0;
	double AtaqueProyectiles = 0.0;
	double AtaqueWrestling = 0.0;
	double DanoArmas = 0.0;
	double DanoProyectiles = 0.0;
	double DanoWrestling = 0.0;
	double Escudo = 0.0;
};

struct ModRaza {
	float Fuerza = 0.0f;
	float Agilidad = 0.0f;
	float Inteligencia = 0.0f;
	float Carisma = 0.0f;
	float Constitucion = 0.0f;
};
/* '[/Pablo ToxicWaste] */

/* '[KEVIN] */
/* 'Banco Objs */
extern const int MAX_BANCOINVENTORY_SLOTS;
/* '[/KEVIN] */

/* '[KEVIN] */
struct BancoInventario {
	BancoInventario() {
		Object.redim(1, MAX_BANCOINVENTORY_SLOTS);
		NroItems = 0;
	}
	vb6::array<struct UserOBJ> Object;
	int NroItems;
};
/* '[/KEVIN] */

/* ' Determina el color del nick */

/* '******* */
/* 'FOROS * */
/* '******* */

/* ' Tipos de mensajes */

/* ' Indica los privilegios para visualizar los diferentes foros */

/* ' Indica el tipo de foro */

/* ' Limite de posts */
extern const int MAX_STICKY_POST;
extern const int MAX_GENERAL_POST;

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
struct tReputacion {
	int NobleRep = 0;
	int BurguesRep = 0;
	int PlebeRep = 0;
	int LadronesRep = 0;
	int BandidoRep = 0;
	int AsesinoRep = 0;
	int Promedio = 0;
};

/* 'Estadisticas de los usuarios */
struct UserStats {
	UserStats() {
		UserSkills.redim(1, NUMSKILLS);
		UserAtributos.redim(1, NUMATRIBUTOS);
		UserAtributosBackUP.redim(1, NUMATRIBUTOS);
		UserHechizos.redim(1, MAXUSERHECHIZOS);
		ExpSkills.redim(1, NUMSKILLS);
		EluSkills.redim(1, NUMSKILLS);
	}

	/* 'Dinero */
	int GLD = 0;
	int Banco = 0;

	int MaxHp = 0;
	int MinHp = 0;

	int MaxSta = 0;
	int MinSta = 0;
	int MaxMAN = 0;
	int MinMAN = 0;
	int MaxHIT = 0;
	int MinHIT = 0;

	int MaxHam = 0;
	int MinHam = 0;

	int MaxAGU = 0;
	int MinAGU = 0;

	int def = 0;
	std::int64_t Exp = 0;
	int ELV = 0;
	int ELU = 0;
	vb6::array<int> UserSkills;
	vb6::array<int> UserAtributos;
	vb6::array<int> UserAtributosBackUP;
	vb6::array<int> UserHechizos;
	int UsuariosMatados = 0;
	int CriminalesMatados = 0;
	int NPCsMuertos = 0;

	int SkillPts = 0;

	vb6::array<int> ExpSkills;
	vb6::array<int> EluSkills;
};

/* 'Flags */
struct UserFlags {
	/* '¿Esta muerto? */
	int Muerto = 0;
	/* '¿Esta escondido? */
	int Escondido = 0;
	/* '¿Esta comerciando? */
	bool Comerciando = false;
	/* '¿Esta online? */
	bool UserLogged = false;
	bool Meditando = false;
	std::string Descuento{};
	int Hambre = 0;
	int Sed = 0;
	int PuedeMoverse = 0;
	int TimerLanzarSpell = 0;
	int PuedeTrabajar = 0;
	int Envenenado = 0;
	int Paralizado = 0;
	int Inmovilizado = 0;
	int Estupidez = 0;
	int Ceguera = 0;
	int invisible = 0;
	int Maldicion = 0;
	int Bendicion = 0;
	int Oculto = 0;
	int Desnudo = 0;
	bool Descansar = false;
	int Hechizo = 0;
	bool TomoPocion = false;
	int TipoPocion = 0;

	bool NoPuedeSerAtacado = false;
	int AtacablePor = 0;
	int ShareNpcWith = 0;

	int Vuela = 0;
	int Navegando = 0;
	bool Seguro = false;
	bool SeguroResu = false;

	int DuracionEfecto = 0;
	/* ' Npc senalado por el usuario */
	int TargetNPC = 0;
	/* ' Tipo del npc senalado */
	eNPCType TargetNpcTipo;
	/* ' Npc que le pertenece (no puede ser atacado) */
	int OwnedNpc = 0;
	int NpcInv = 0;

	int Ban = 0;
	int AdministrativeBan = 0;

	/* ' Usuario senalado */
	int TargetUser = 0;

	/* ' Obj senalado */
	int TargetObj = 0;
	int TargetObjMap = 0;
	int TargetObjX = 0;
	int TargetObjY = 0;

	int TargetMap = 0;
	int TargetX = 0;
	int TargetY = 0;

	int TargetObjInvIndex = 0;
	int TargetObjInvSlot = 0;

	int AtacadoPorNpc = 0;
	int AtacadoPorUser = 0;
	int NPCAtacado = 0;
	bool Ignorado = false;

	bool EnConsulta = false;
	bool SendDenounces = false;

	int StatsChanged = 0;
	unsigned int Privilegios2 = 0;
	bool PrivEspecial = false;

	int ValCoDe = 0;

	std::string LastCrimMatado;
	std::string LastCiudMatado;

	int OldBody = 0;
	int OldHead = 0;
	int AdminInvisible = 0;
	bool AdminPerseguible = false;

	int ChatColor = 0;

	/* '[el oso] */
	std::string MD5Reportado;
	/* '[/el oso] */

	/* '[Barrin 30-11-03] */
	int TimesWalk = 0;
	int StartWalk = 0;
	int CountSH = 0;
	/* '[/Barrin 30-11-03] */

	/* '[CDT 17-02-04] */
	int UltimoMensaje = 0;
	/* '[/CDT] */

	int Silenciado = 0;

	int Mimetizado = 0;

	/* ' Indice del centinela que lo revisa */
	int CentinelaIndex = 0;
	bool CentinelaOK = false;

	int lastMap = 0;
	/* 'Travelin Band ¿? */
	int Traveling = 0;

	std::string ParalizedBy;
	int ParalizedByIndex = 0;
	int ParalizedByNpcIndex = 0;

	/* # IF SeguridadAlkon THEN */
	/* # END IF */
};

struct UserCounters {
	int IdleCount = 0;
	int AttackCounter = 0;
	int HPCounter = 0;
	int STACounter = 0;
	int Frio = 0;
	int Lava = 0;
	int COMCounter = 0;
	int AGUACounter = 0;
	int Veneno = 0;
	int Paralisis = 0;
	int Ceguera = 0;
	int Estupidez = 0;

	int Invisibilidad = 0;
	int TiempoOculto = 0;

	int Mimetismo = 0;
	int PiqueteC = 0;
	int Pena = 0;
	struct WorldPos SendMapCounter;
	/* '[Gonzalo] */
	bool Saliendo = false;
	int Salir = 0;
	/* '[/Gonzalo] */

	/* 'Barrin 3/10/03 */
	int tInicioMeditar = 0;
	bool bPuedeMeditar = false;
	/* 'Barrin */

	int TimerLanzarSpell = 0;
	int TimerPuedeAtacar = 0;
	int TimerPuedeUsarArco = 0;
	int TimerPuedeTrabajar = 0;
	int TimerUsar = 0;
	int TimerMagiaGolpe = 0;
	int TimerGolpeMagia = 0;
	int TimerGolpeUsar = 0;
	int TimerPuedeSerAtacado = 0;
	int TimerPerteneceNpc = 0;
	int TimerEstadoAtacable = 0;

	/* ' Para el centinela */
	int Trabajando = 0;
	/* ' Unico trabajo no revisado por el centinela */
	int Ocultando = 0;

	int failedUsageAttempts = 0;

	int goHome = 0;
	int AsignedSkills = 0;
};

/* 'Cosas faccionarias. */
struct tFacciones {
	int ArmadaReal = 0;
	int FuerzasCaos = 0;
	int CriminalesMatados = 0;
	int CiudadanosMatados = 0;
	int RecompensasReal = 0;
	int RecompensasCaos = 0;
	int RecibioExpInicialReal = 0;
	int RecibioExpInicialCaos = 0;
	int RecibioArmaduraReal = 0;
	int RecibioArmaduraCaos = 0;
	int Reenlistadas = 0;
	int NivelIngreso = 0;
	std::string FechaIngreso;
	/* 'Para Armadas nada mas */
	int MatadosIngreso = 0;
	int NextRecompensa = 0;
};

struct tCrafting {
	int Cantidad = 0;
	int PorCiclo = 0;
};

/* 'Tipo de los Usuarios */
struct User {
	User() {
		MascotasIndex.redim(1, MAXMASCOTAS);
		MascotasType.redim(1, MAXMASCOTAS);
	}
	std::string Name;
	int ID = 0;

	/* 'Permite que los GMs oculten su nick con el comando /SHOWNAME */
	bool showName = false;

	/* 'Define la apariencia */
	struct Char Char{};
	struct Char CharMimetizado{};
	struct Char OrigChar{};

	/* ' Descripcion */
	std::string desc;
	std::string DescRM;

	eClass clase = eClass_None;
	eRaza raza = eRaza_None;
	eGenero Genero = eGenero_None;
	std::string email;
	eCiudad Hogar = eCiudad_None;

	struct Inventario Invent;

	struct WorldPos Pos{};

	bool ConnIgnoreIncomingData = false;
	bool IncomingDataAvailable = false;

	/* 'ID */
	class dakara::Socket* sockctx = 0;
	std::shared_ptr<clsByteQueue> outgoingData;
	std::shared_ptr<clsByteQueue> incomingData;

	/* '[KEVIN] */
	struct BancoInventario BancoInvent;
	/* '[/KEVIN] */

	struct UserCounters Counters{};

	struct tCrafting Construir{};

	vb6::array<int> MascotasIndex;
	vb6::array<int> MascotasType;
	int NroMascotas = 0;

	struct UserStats Stats{};
	struct UserFlags flags{};

	struct tReputacion Reputacion{};

	struct tFacciones Faccion{};

	boost::posix_time::ptime LogOnTime{};
	int UpTime = 0;

	std::string ip;

	struct tCOmercioUsuario ComUsu;

	/* 'puntero al array global de guilds */
	int GuildIndex = 0;
	/* 'esto esta aca hasta que se parchee el cliente y se pongan cadenas de datos distintas para cada alineacion */
	ALINEACION_GUILD FundandoGuildAlineacion = ALINEACION_GUILD_Null;
	int EscucheClan = 0;

	/* 'index a la party q es miembro */
	int PartyIndex = 0;
	/* 'index a la party q solicito */
	int PartySolicitud = 0;

	int KeyCrypt = 0;

	struct AreaInfo AreasInfo;

	int CurrentInventorySlots = 0;
};

/* '********************************************************* */
/* '********************************************************* */
/* '********************************************************* */
/* '********************************************************* */
/* '**  T I P O S   D E    N P C S ************************** */
/* '********************************************************* */
/* '********************************************************* */
/* '********************************************************* */
/* '********************************************************* */

struct NPCStats {
	int Alineacion = 0;
	int MaxHp = 0;
	int MinHp = 0;
	int MaxHIT = 0;
	int MinHIT = 0;
	int def = 0;
	int defM = 0;
};

struct NpcCounters {
	int Paralisis = 0;
	int TiempoExistencia = 0;
};

struct NPCFlags {
	NPCFlags() : NPCActive(false) {}

	int AfectaParalisis{};
	int Domable{};
	int Respawn{};
	/* '¿Esta vivo? */
	bool NPCActive{};
	bool Follow{};
	int Faccion{};
	int AtacaDoble{};
	int LanzaSpells{};

	int ExpCount{};

	TipoAI OldMovement{};
	int OldHostil{};

	int AguaValida{};
	int TierraInvalida{};

	int Sound{};
	std::string AttackedBy{};
	std::string AttackedFirstBy{};
	int BackUp{};
	int RespawnOrigPos{};

	int Envenenado{};
	int Paralizado{};
	int Inmovilizado{};
	int invisible{};
	int Maldicion{};
	int Bendicion{};

	int Snd1{};
	int Snd2{};
	int Snd3{};
};

struct tCriaturasEntrenador {
	int NpcIndex{};
	std::string NpcName{};
	int tmpIndex{};
};

struct tVertice {
	int X = 0, Y = 0;
};

/* ' New type for holding the pathfinding info */
struct NpcPathFindingInfo {
	/* ' This array holds the path */
	vb6::array<struct Position> Path;
	/* ' The location where the NPC has to go */
	struct Position Target;
	/* ' Number of steps * */
	int PathLenght{};
	/* ' Current location of the npc */
	int CurPos{};
	/* ' UserIndex chased */
	int TargetUser{};
	/* ' If it is true there is no path to the target location */
	bool NoPath{};

	/* '* By setting PathLenght to 0 we force the recalculation */
	/* '  of the path, this is very useful. For example, */
	/* '  if a NPC or a User moves over the npc's path, blocking */
	/* '  its way, the function NpcLegalPos set PathLenght to 0 */
	/* '  forcing the seek of a new path. */

};
/* ' New type for holding the pathfinding info */

struct tDrops {
	int ObjIndex{};
	int Amount{};
};

extern const int MAX_NPC_DROPS;

struct npc {
	npc() {
		Drop.redim(1, MAX_NPC_DROPS);
		Numero = 0;
	}

	std::string Name{};
	/* 'Define como se vera */
	struct Char Char{};
	std::string desc{};

	eNPCType NPCtype{};
	int Numero{};

	int InvReSpawn{};

	int Comercia{};
	int Target{};
	int TargetNPC{};
	int TipoItems{};

	int Veneno{};

	/* 'Posicion */
	struct WorldPos Pos{};
	struct WorldPos Orig{};
	int SkillDomar{};

	TipoAI Movement{};
	int Attackable{};
	int Hostile{};
	int PoderAtaque{};
	int PoderEvasion{};

	int Owner{};

	int GiveEXP{};
	int GiveGLD{};
	vb6::array<struct tDrops> Drop{};

	struct NPCStats Stats{};
	struct NPCFlags flags{};
	struct NpcCounters Contadores{};

	struct Inventario Invent{};
	int CanAttack{};

	int NroExpresiones{};
	/* ' le da vida {};) */
	vb6::array<std::string> Expresiones{};

	int NroSpells{};
	/* ' le da vida {};) */
	vb6::array<int> Spells{};

	/* '<<<<Entrenadores>>>>> */
	int NroCriaturas{};
	vb6::array<struct tCriaturasEntrenador> Criaturas{};
	int MaestroUser{};
	int MaestroNpc{};
	int Mascotas{};

	/* ' New!! Needed for pathfindig */
	struct NpcPathFindingInfo PFINFO{};
	struct AreaInfo AreasInfo{};

	/* 'Hogar */
	int Ciudad{};

	/* 'Para diferenciar entre clanes */
	int ClanIndex{};
};

/* '********************************************************** */
/* '********************************************************** */
/* '******************** Tipos del mapa ********************** */
/* '********************************************************** */
/* '********************************************************** */
/* 'Tile */
struct MapBlock {
	MapBlock() {
		Graphic.redim(1, 4);
		Blocked = 0;
		UserIndex = 0;
		NpcIndex = 0;
		trigger = eTrigger_NADA;
	}
	int Blocked;
	vb6::array<int> Graphic;
	int UserIndex;
	int NpcIndex;
	struct Obj ObjInfo{};
	struct WorldPos TileExit{};
	eTrigger trigger;
};

/* 'Info del mapa */
struct MapInfo {
	int NumUsers{};
	int Music{};
	std::string Name{};
	struct WorldPos StartPos{};
	struct WorldPos OnDeathGoTo{};

	int MapVersion{};
	bool Pk{};
	int MagiaSinEfecto{};
	int NoEncriptarMP{};

	/* ' Anti Magias/Habilidades */
	int InviSinEfecto{};
	int ResuSinEfecto{};
	int OcultarSinEfecto{};
	int InvocarSinEfecto{};

	int RoboNpcsPermitido{};

	int Terreno{};
	std::string Zona{};
	int Restringir{};
	int BackUp{};
};

/* '********** V A R I A B L E S     P U B L I C A S *********** */

extern bool SERVERONLINE;
extern std::string ULTIMAVERSION;
/* ' TODO: Se usa esta variable ? */
extern bool BackUp;

extern vb6::array<std::string> ListaRazas;
extern vb6::array<std::string> SkillsNames;
extern vb6::array<std::string> ListaClases;
extern vb6::array<std::string> ListaAtributos;

extern int RECORDusuarios;

/* '' */
/* 'Bordes del mapa */
extern int MinXBorder;
extern int MaxXBorder;
extern int MinYBorder;
extern int MaxYBorder;

/* '' */
/* 'Numero de usuarios actual */
extern int NumUsers;
extern int LastUser;
extern int LastChar;
extern int NumChars;
extern int LastNPC;
extern int NumNPCs;
extern int NumFX;
extern int NumMaps;
extern int NumObjDatas;
extern int NumeroHechizos;
extern int AllowMultiLogins;
extern int LimiteConexionesPorIp;
extern int IdleLimit;
extern int MaxUsers;
extern int HideMe;
extern std::string LastBackup;
extern std::string Minutos;
extern bool haciendoBK;
extern int PuedeCrearPersonajes;
extern int ServerSoloGMs;
extern int NumRecords;
extern float HappyHour;
extern bool HappyHourActivated;
extern vb6::array<float> HappyHourDays;

extern int RegistroListaBlancaEmails;
extern std::set<std::string> RegistroEmailsHabilitados;

/* '' */
/* 'Esta activada la verificacion MD5 ? */
extern int MD5ClientesActivado;

extern bool EnPausa;
extern bool EnTesting;

/* '*****************ARRAYS PUBLICOS************************* */
/* 'USUARIOS */
extern vb6::array<struct User> UserList;
/* 'NPCS */
extern vb6::array<struct npc> Npclist;
extern vb6::array<vb6::array<vb6::array<struct MapBlock> > > MapData;
extern vb6::array<struct MapInfo> MapInfo;
extern vb6::array<struct tHechizo> Hechizos;
extern vb6::array<int> CharList;
extern vb6::array<struct ObjData> ObjData;
//extern vb6::array<struct FXdata> FX;
extern vb6::array<struct tCriaturasEntrenador> SpawnList;
extern vb6::array<struct LevelSkill> LevelSkill;
extern vb6::array<std::string> ForbidenNames;
extern vb6::array<int> ArmasHerrero;
extern vb6::array<int> ArmadurasHerrero;
extern vb6::array<int> ObjCarpintero;
extern std::vector<std::string> MD5s;
extern std::set<std::string> BanIps;
extern vb6::array<std::shared_ptr<clsParty>> Parties;
extern vb6::array<struct ModClase> ModClase;
extern vb6::array<struct ModRaza> ModRaza;
extern vb6::array<double> ModVida;
extern vb6::array<int> DistribucionEnteraVida;
extern vb6::array<int> DistribucionSemienteraVida;
extern vb6::array<struct WorldPos> Ciudades;
extern vb6::array<struct HomeDistance> distanceToCities;
extern vb6::array<struct tRecord> Records;
/* '********************************************************* */

struct HomeDistance {
	HomeDistance() {
		distanceToCity.redim(1, NUMCIUDADES);
	}
	vb6::array<int> distanceToCity;
};

extern struct WorldPos Nix;
extern struct WorldPos Ullathorpe;
extern struct WorldPos Banderbill;
extern struct WorldPos Lindos;
extern struct WorldPos Arghal;
extern struct WorldPos Arkhein;
extern struct WorldPos Nemahuak;

extern struct WorldPos Prision;
extern struct WorldPos Libertad;

//extern std::shared_ptr<cCola> Ayuda;
//extern std::shared_ptr<cCola> Denuncias;
extern std::deque<std::string> Ayuda;
extern std::deque<std::string> Denuncias;
extern std::shared_ptr<ConsultasPopulares> ConsultaPopular;
extern std::shared_ptr<SoundMapInfo> SonidosMapas;

extern const int MATRIX_INITIAL_MAP;

extern const int GOHOME_PENALTY;
extern const int GM_MAP;

extern const int TELEP_OBJ_INDEX;

extern const int HUMANO_H_PRIMER_CABEZA;
/* 'En verdad es hasta la 51, pero como son muchas estas las dejamos no seleccionables */
extern const int HUMANO_H_ULTIMA_CABEZA;

extern const int ELFO_H_PRIMER_CABEZA;
extern const int ELFO_H_ULTIMA_CABEZA;

extern const int DROW_H_PRIMER_CABEZA;
extern const int DROW_H_ULTIMA_CABEZA;

extern const int ENANO_H_PRIMER_CABEZA;
extern const int ENANO_H_ULTIMA_CABEZA;

extern const int GNOMO_H_PRIMER_CABEZA;
extern const int GNOMO_H_ULTIMA_CABEZA;
/* '************************************************** */
extern const int HUMANO_M_PRIMER_CABEZA;
extern const int HUMANO_M_ULTIMA_CABEZA;

extern const int ELFO_M_PRIMER_CABEZA;
extern const int ELFO_M_ULTIMA_CABEZA;

extern const int DROW_M_PRIMER_CABEZA;
extern const int DROW_M_ULTIMA_CABEZA;

extern const int ENANO_M_PRIMER_CABEZA;
extern const int ENANO_M_ULTIMA_CABEZA;

extern const int GNOMO_M_PRIMER_CABEZA;
extern const int GNOMO_M_ULTIMA_CABEZA;

/* ' Por ahora la dejo constante.. SI se quisiera extender la propiedad de paralziar, se podria hacer */
/* ' una nueva variable en el dat. */
extern const int GUANTE_HURTO;

extern const int ESPADA_VIKINGA;
/* ''''''' */
/* '' Pretorianos */
/* ''''''' */
/* FIXME: PRETORIANOS */

// extern vb6::array<std::shared_ptr<clsClanPretoriano>> ClanPretoriano;

extern const int MAX_DENOUNCES;
extern const int MAX_PENAS;
extern const int MAX_SPECIAL_USERS;
extern const int MAX_MAPS;
extern const int MAX_EXPRESIONES;
extern const int MAX_SONIDOS;
extern const int MAX_DAT_ITEMS;
extern const int MAX_CRIATURAS_ENTRENADOR;
extern const int MAX_HELP_LINES;

/* 'Mensajes de los NPCs enlistadores (Nobles): */
extern const std::string MENSAJE_REY_CAOS;
extern const std::string MENSAJE_REY_CRIMINAL_NOENLISTABLE;
extern const std::string MENSAJE_REY_CRIMINAL_ENLISTABLE;

extern const std::string MENSAJE_DEMONIO_REAL;
extern const std::string MENSAJE_DEMONIO_CIUDADANO_NOENLISTABLE;
extern const std::string MENSAJE_DEMONIO_CIUDADANO_ENLISTABLE;

extern std::shared_ptr<clsIniManager> Administradores;

extern const int MIN_AMOUNT_LOG;
extern const int MIN_VALUE_LOG;
extern const int MIN_GOLD_AMOUNT_LOG;

/* 'TODO:Esto hay que volarlo, es temporal! */
//extern std::string GUILDPATH;
//extern std::string GUILDINFOFILE;

extern std::string DakaraBasePath;

#endif
