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

#include "Forum.h"

const int MAX_MENSAJES_FORO = 30;
const int MAX_ANUNCIOS_FORO = 5;

const std::string FORO_REAL_ID = "REAL";
const std::string FORO_CAOS_ID = "CAOS";

static int NumForos;
static vb6::array<struct tForo> Foros;

void AddForum(std::string sForoID) {
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 22/02/2010 */
	/* 'Adds a forum to the list and fills it. */
	/* '*************************************************** */
	std::string ForumPath;
	std::string PostPath;
	int PostIndex;

	NumForos = NumForos + 1;
	Foros.redim(1, NumForos);

	ForumPath = GetForumPath(sForoID);

	Foros[NumForos].ID = sForoID;

	if (FileExist(ForumPath, 0)) {
		Foros[NumForos].CantPosts = vb6::Constrain(vb6::CInt(GetVar(ForumPath, "INFO", "CantMSG")), 0, MAX_MENSAJES_FORO);
		Foros[NumForos].CantAnuncios = vb6::Constrain(vb6::CInt(GetVar(ForumPath, "INFO", "CantAnuncios")), 0, MAX_ANUNCIOS_FORO);

		/* ' Cargo posts */
		for (PostIndex = (1); PostIndex <= (Foros[NumForos].CantPosts); PostIndex++) {
			PostPath = GetForumMsgPath(sForoID, PostIndex, true);

			/* FIXME: OPEN PostPath FOR INPUT Shared AS # FileIndex */

			/* ' Titulo */
			/* FIXME: INPUT # FileIndex , . vsPost ( PostIndex ) . sTitulo */
			/* ' Autor */
			/* FIXME: INPUT # FileIndex , . vsPost ( PostIndex ) . Autor */
			/* ' Mensaje */
			/* FIXME: INPUT # FileIndex , . vsPost ( PostIndex ) . sPost */

			/* FIXME: CLOSE # FileIndex */
		}

		/* ' Cargo anuncios */
		for (PostIndex = (1); PostIndex <= (Foros[NumForos].CantAnuncios); PostIndex++) {
			PostPath = GetForumMsgPath(sForoID, PostIndex, false);

			/* FIXME: OPEN PostPath FOR INPUT Shared AS # FileIndex */

			/* ' Titulo */
			/* FIXME: INPUT # FileIndex , . vsAnuncio ( PostIndex ) . sTitulo */
			/* ' Autor */
			/* FIXME: INPUT # FileIndex , . vsAnuncio ( PostIndex ) . Autor */
			/* ' Mensaje */
			/* FIXME: INPUT # FileIndex , . vsAnuncio ( PostIndex ) . sPost */

			/* FIXME: CLOSE # FileIndex */
		}
	}

}

int GetForumIndex(const std::string & sForoID) {
	int retval = 0;
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 22/02/2010 */
	/* 'Returns the forum index. */
	/* '*************************************************** */

	int ForumIndex;

	for (ForumIndex = (1); ForumIndex <= (NumForos); ForumIndex++) {
		if (Foros[ForumIndex].ID == sForoID) {
			retval = ForumIndex;
			return retval;
		}
	}

	return retval;
}

void AddPost(int ForumIndex, std::string & Post, std::string & Autor, std::string & Titulo, bool bAnuncio) {
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 22/02/2010 */
	/* 'Saves a new post into the forum. */
	/* '*************************************************** */

	if (bAnuncio) {
		if (Foros[ForumIndex].CantAnuncios < MAX_ANUNCIOS_FORO) {
			Foros[ForumIndex].CantAnuncios = Foros[ForumIndex].CantAnuncios + 1;
		}

		MoveArray(ForumIndex, bAnuncio);

		/* ' Agrego el anuncio */
		Foros[ForumIndex].vsAnuncio[1].sTitulo = Titulo;
		Foros[ForumIndex].vsAnuncio[1].Autor = Autor;
		Foros[ForumIndex].vsAnuncio[1].sPost = Post;

	} else {
		if (Foros[ForumIndex].CantPosts < MAX_MENSAJES_FORO) {
			Foros[ForumIndex].CantPosts = Foros[ForumIndex].CantPosts + 1;
		}

		MoveArray(ForumIndex, bAnuncio);

		/* ' Agrego el post */
		Foros[ForumIndex].vsPost[1].sTitulo = Titulo;
		Foros[ForumIndex].vsPost[1].Autor = Autor;
		Foros[ForumIndex].vsPost[1].sPost = Post;

	}
}

void SaveForums() {
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 22/02/2010 */
	/* 'Saves all forums into disk. */
	/* '*************************************************** */
	int ForumIndex;

	for (ForumIndex = (1); ForumIndex <= (NumForos); ForumIndex++) {
		SaveForum(ForumIndex);
	}
}

void SaveForum(int ForumIndex) {
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 22/02/2010 */
	/* 'Saves a forum into disk. */
	/* '*************************************************** */

	int PostIndex;
	std::string PostPath;

	CleanForum(ForumIndex);

	/* ' Guardo info del foro */
	WriteVar(GetForumPath(Foros[ForumIndex].ID), "INFO", "CantMSG",
			Foros[ForumIndex].CantPosts);
	WriteVar(GetForumPath(Foros[ForumIndex].ID), "INFO", "CantAnuncios",
			Foros[ForumIndex].CantAnuncios);

	/* ' Guardo posts */
	for (PostIndex = (1); PostIndex <= (Foros[ForumIndex].CantPosts); PostIndex++) {

		PostPath = GetForumMsgPath(Foros[ForumIndex].ID, PostIndex, true);
		/* FIXME: OPEN PostPath FOR OUTPUT AS FileIndex */

		/* FIXME: PRINT # FileIndex , . sTitulo */
		/* FIXME: PRINT # FileIndex , . Autor */
		/* FIXME: PRINT # FileIndex , . sPost */

		/* FIXME: CLOSE # FileIndex */

	}

	/* ' Guardo Anuncios */
	for (PostIndex = (1); PostIndex <= (Foros[ForumIndex].CantAnuncios); PostIndex++) {

		PostPath = GetForumMsgPath(Foros[ForumIndex].ID, PostIndex, false);
		/* FIXME: OPEN PostPath FOR OUTPUT AS FileIndex */

		/* FIXME: PRINT # FileIndex , . sTitulo */
		/* FIXME: PRINT # FileIndex , . Autor */
		/* FIXME: PRINT # FileIndex , . sPost */

		/* FIXME: CLOSE # FileIndex */

	}

}

void CleanForum(int ForumIndex) {
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 22/02/2010 */
	/* 'Cleans a forum from disk. */
	/* '*************************************************** */
	int PostIndex;
	int NumPost;
	std::string ForumPath;

	/* ' Elimino todo */
	ForumPath = GetForumPath(Foros[ForumIndex].ID);
	if (FileExist(ForumPath, 0)) {

		NumPost = vb6::Constrain(vb6::CInt(GetVar(ForumPath, "INFO", "CantMSG")), 0, MAX_MENSAJES_FORO);

		/* ' Elimino los post viejos */
		for (PostIndex = (1); PostIndex <= (NumPost); PostIndex++) {
			/* FIXME: KILL App . Path & "/Foros/" & . ID & PostIndex & ".for" */
		}

		NumPost = vb6::Constrain(vb6::CInt(GetVar(ForumPath, "INFO", "CantAnuncios")), 0, MAX_ANUNCIOS_FORO);

		/* ' Elimino los post viejos */
		for (PostIndex = (1); PostIndex <= (NumPost); PostIndex++) {
			/* FIXME: KILL App . Path & "/Foros/" & . ID & PostIndex & "a.for" */
		}

		/* ' Elimino el foro */
		/* FIXME: KILL App . Path & "/Foros/" & . ID & ".for" */

	}

}

bool SendPosts(int UserIndex, std::string & ForoID) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 22/02/2010 */
	/* 'Sends all the posts of a required forum */
	/* '*************************************************** */

	int ForumIndex;
	int PostIndex;
	bool bEsGm;

	ForumIndex = GetForumIndex(ForoID);

	if (ForumIndex > 0) {

		/* ' Send General posts */
		for (PostIndex = (1); PostIndex <= (Foros[ForumIndex].CantPosts); PostIndex++) {
			WriteAddForumMsg(UserIndex, eForumMsgType_ieGeneral, Foros[ForumIndex].vsPost[PostIndex].sTitulo,
					Foros[ForumIndex].vsPost[PostIndex].Autor, Foros[ForumIndex].vsPost[PostIndex].sPost);
		}

		/* ' Send Sticky posts */
		for (PostIndex = (1); PostIndex <= (Foros[ForumIndex].CantAnuncios); PostIndex++) {
			WriteAddForumMsg(UserIndex, eForumMsgType_ieGENERAL_STICKY,
					Foros[ForumIndex].vsAnuncio[PostIndex].sTitulo,
					Foros[ForumIndex].vsAnuncio[PostIndex].Autor,
					Foros[ForumIndex].vsAnuncio[PostIndex].sPost);
		}

		bEsGm = EsGm(UserIndex);

		/* ' Caos? */
		if (esCaos(UserIndex) || bEsGm) {

			ForumIndex = GetForumIndex(FORO_CAOS_ID);

			/* ' Send General Caos posts */
			for (PostIndex = (1); PostIndex <= (Foros[ForumIndex].CantPosts); PostIndex++) {

				WriteAddForumMsg(UserIndex, eForumMsgType_ieCAOS, Foros[ForumIndex].vsPost[PostIndex].sTitulo,
						Foros[ForumIndex].vsPost[PostIndex].Autor, Foros[ForumIndex].vsPost[PostIndex].sPost);

			}

			/* ' Send Sticky posts */
			for (PostIndex = (1); PostIndex <= (Foros[ForumIndex].CantAnuncios); PostIndex++) {
				WriteAddForumMsg(UserIndex, eForumMsgType_ieCAOS_STICKY,
						Foros[ForumIndex].vsAnuncio[PostIndex].sTitulo,
						Foros[ForumIndex].vsAnuncio[PostIndex].Autor,
						Foros[ForumIndex].vsAnuncio[PostIndex].sPost);
			}

		}

		/* ' Caos? */
		if (esArmada(UserIndex) || bEsGm) {

			ForumIndex = GetForumIndex(FORO_REAL_ID);

			/* ' Send General Real posts */
			for (PostIndex = (1); PostIndex <= (Foros[ForumIndex].CantPosts); PostIndex++) {

				WriteAddForumMsg(UserIndex, eForumMsgType_ieREAL, Foros[ForumIndex].vsPost[PostIndex].sTitulo,
						Foros[ForumIndex].vsPost[PostIndex].Autor, Foros[ForumIndex].vsPost[PostIndex].sPost);

			}

			/* ' Send Sticky posts */
			for (PostIndex = (1); PostIndex <= (Foros[ForumIndex].CantAnuncios); PostIndex++) {
				WriteAddForumMsg(UserIndex, eForumMsgType_ieREAL_STICKY,
						Foros[ForumIndex].vsAnuncio[PostIndex].sTitulo,
						Foros[ForumIndex].vsAnuncio[PostIndex].Autor,
						Foros[ForumIndex].vsAnuncio[PostIndex].sPost);
			}

		}

		retval = true;
	}

	return retval;
}

bool EsAnuncio(int ForumType) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 22/02/2010 */
	/* 'Returns true if the post is sticky. */
	/* '*************************************************** */
	switch (ForumType) {
	case eForumMsgType_ieCAOS_STICKY:
		retval = true;

		break;

	case eForumMsgType_ieGENERAL_STICKY:
		retval = true;

		break;

	case eForumMsgType_ieREAL_STICKY:
		retval = true;

		break;
	}

	return retval;
}

int ForumAlignment(int yForumType) {
	int retval = 0;
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 01/03/2010 */
	/* 'Returns the forum alignment. */
	/* '*************************************************** */
	switch (yForumType) {
	case eForumMsgType_ieCAOS:
	case eForumMsgType_ieCAOS_STICKY:
		retval = eForumType_ieCAOS;

		break;

	case eForumMsgType_ieGeneral:
	case eForumMsgType_ieGENERAL_STICKY:
		retval = eForumType_ieGeneral;

		break;

	case eForumMsgType_ieREAL:
	case eForumMsgType_ieREAL_STICKY:
		retval = eForumType_ieREAL;

		break;
	}

	return retval;
}

void ResetForums() {
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 22/02/2010 */
	/* 'Resets forum info */
	/* '*************************************************** */
	Foros.redim(0);
	Foros.redim(1, 1);
	NumForos = 0;
}

void MoveArray(int ForumIndex, bool Sticky) {
	int i;

	if (Sticky) {
		for (i = (Foros[ForumIndex].CantAnuncios); ((-1) > 0) ? (i <= (2)) : (i >= (2)); i = i + (-1)) {
			Foros[ForumIndex].vsAnuncio[i].sTitulo = Foros[ForumIndex].vsAnuncio[i - 1].sTitulo;
			Foros[ForumIndex].vsAnuncio[i].sPost = Foros[ForumIndex].vsAnuncio[i - 1].sPost;
			Foros[ForumIndex].vsAnuncio[i].Autor = Foros[ForumIndex].vsAnuncio[i - 1].Autor;
		}
	} else {
		for (i = (Foros[ForumIndex].CantPosts); ((-1) > 0) ? (i <= (2)) : (i >= (2)); i = i + (-1)) {
			Foros[ForumIndex].vsPost[i].sTitulo = Foros[ForumIndex].vsPost[i - 1].sTitulo;
			Foros[ForumIndex].vsPost[i].sPost = Foros[ForumIndex].vsPost[i - 1].sPost;
			Foros[ForumIndex].vsPost[i].Autor = Foros[ForumIndex].vsPost[i - 1].Autor;
		}
	}
}
