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

#ifndef MODFORUM_H
#define MODFORUM_H
#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"

extern const int MAX_MENSAJES_FORO;
extern const int MAX_ANUNCIOS_FORO;

extern const std::string FORO_REAL_ID;
extern const std::string FORO_CAOS_ID;

struct tPost {
	std::string sTitulo;
	std::string sPost;
	std::string Autor;
};

struct tForo {
	tForo() {
		vsPost.redim(1, MAX_MENSAJES_FORO);
		vsAnuncio.redim(1, MAX_ANUNCIOS_FORO);
	}

	vb6::array<struct tPost> vsPost;
	vb6::array<struct tPost> vsAnuncio;
	int CantPosts = 0;
	int CantAnuncios = 0;
	std::string ID;
};

void AddForum(std::string sForoID);

int GetForumIndex(const std::string & sForoID);

void AddPost(int ForumIndex, std::string & Post, std::string & Autor, std::string & Titulo, bool bAnuncio);

void SaveForums();

void SaveForum(int ForumIndex);

void CleanForum(int ForumIndex);

bool SendPosts(int UserIndex, std::string & ForoID);

bool EsAnuncio(int ForumType);

int ForumAlignment(int yForumType);

void ResetForums();

void MoveArray(int ForumIndex, bool Sticky);

#endif
