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

#ifndef MDLCOMERCIOCONUSUARIO_H
#define MDLCOMERCIOCONUSUARIO_H
#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"

/* '[Alejo] */

extern const int MAX_OFFER_SLOTS;
extern const int GOLD_OFFER_SLOT;

struct tCOmercioUsuario {
	tCOmercioUsuario() {
		Objeto.redim(1, MAX_OFFER_SLOTS);
		cant.redim(1, MAX_OFFER_SLOTS);
	}
	/* 'El otro Usuario */
	int DestUsu = 0;
	std::string DestNick;
	/* 'Indice de los objetos que se desea dar */
	vb6::array<int> Objeto;
	int GoldAmount = 0;

	/* 'Cuantos objetos desea dar */
	vb6::array<int> cant;
	bool Acepto = false;
	bool Confirmo = false;
};

struct tOfferItem {
	int ObjIndex = 0;
	int Amount = 0;
};

/* 'origen: origen de la transaccion, originador del comando */
/* 'destino: receptor de la transaccion */
void IniciarComercioConUsuario(int Origen, int Destino);

void EnviarOferta(int UserIndex, int OfferSlot);

void FinComerciarUsu(int UserIndex);

void AceptarComercioUsu(int UserIndex);

void AgregarOferta(int UserIndex, int OfferSlot, int ObjIndex, int Amount, bool IsGold);

bool PuedeSeguirComerciando(int UserIndex);

bool HasOfferedItems(int UserIndex);

#endif
