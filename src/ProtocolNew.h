
/* Automatically generated file */

#ifndef DAKARAPROTOCOLNEW_H
#define DAKARAPROTOCOLNEW_H

#include <stdint.h>
#include <string>
#include <vector>
#include <stdexcept>
#include <memory>

#include "ByteQueue.h"

namespace dakara {
namespace protocol {

namespace clientgm {
    class ClientGMPacket;
}

namespace client {
    class ClientPacketHandler;
}
namespace clientgm {
    class ClientGMPacketHandler;
}
namespace server {
    class ServerPacketHandler;
}

class PacketDecodingError : public std::runtime_error {
public:
    PacketDecodingError(const std::string& what) : std::runtime_error(what) {}
};

class PacketHandler {
public:
    virtual ~PacketHandler() {};
    virtual client::ClientPacketHandler* getPacketHandlerClientPacket() = 0;
    virtual clientgm::ClientGMPacketHandler* getPacketHandlerClientGMPacket() = 0;
    virtual server::ServerPacketHandler* getPacketHandlerServerPacket() = 0;
};

class Packet {
public:
    explicit Packet(int id) : id_(id) {}
    virtual ~Packet() {}

    int get_id() const { return id_; }

    virtual void serialize(clsByteQueue* buffer) const = 0;
    virtual void dispatch(PacketHandler* d) = 0;

protected:
    int id_;
};


namespace client {
enum ClientPacketID { 
    ClientPacketID_LoginExistingChar = 0,
    ClientPacketID_ThrowDices = 1,
    ClientPacketID_LoginNewChar = 2,
    ClientPacketID_Talk = 3,
    ClientPacketID_Yell = 4,
    ClientPacketID_Whisper = 5,
    ClientPacketID_Walk = 6,
    ClientPacketID_RequestPositionUpdate = 7,
    ClientPacketID_Attack = 8,
    ClientPacketID_PickUp = 9,
    ClientPacketID_SafeToggle = 10,
    ClientPacketID_ResuscitationSafeToggle = 11,
    ClientPacketID_RequestGuildLeaderInfo = 12,
    ClientPacketID_RequestAtributes = 13,
    ClientPacketID_RequestFame = 14,
    ClientPacketID_RequestSkills = 15,
    ClientPacketID_RequestMiniStats = 16,
    ClientPacketID_CommerceEnd = 17,
    ClientPacketID_UserCommerceEnd = 18,
    ClientPacketID_UserCommerceConfirm = 19,
    ClientPacketID_CommerceChat = 20,
    ClientPacketID_BankEnd = 21,
    ClientPacketID_UserCommerceOk = 22,
    ClientPacketID_UserCommerceReject = 23,
    ClientPacketID_Drop = 24,
    ClientPacketID_CastSpell = 25,
    ClientPacketID_LeftClick = 26,
    ClientPacketID_DoubleClick = 27,
    ClientPacketID_Work = 28,
    ClientPacketID_UseSpellMacro = 29,
    ClientPacketID_UseItem = 30,
    ClientPacketID_CraftBlacksmith = 31,
    ClientPacketID_CraftCarpenter = 32,
    ClientPacketID_WorkLeftClick = 33,
    ClientPacketID_CreateNewGuild = 34,
    ClientPacketID_SpellInfo = 35,
    ClientPacketID_EquipItem = 36,
    ClientPacketID_ChangeHeading = 37,
    ClientPacketID_ModifySkills = 38,
    ClientPacketID_Train = 39,
    ClientPacketID_CommerceBuy = 40,
    ClientPacketID_BankExtractItem = 41,
    ClientPacketID_CommerceSell = 42,
    ClientPacketID_BankDeposit = 43,
    ClientPacketID_ForumPost = 44,
    ClientPacketID_MoveSpell = 45,
    ClientPacketID_MoveBank = 46,
    ClientPacketID_ClanCodexUpdate = 47,
    ClientPacketID_UserCommerceOffer = 48,
    ClientPacketID_GuildAcceptPeace = 49,
    ClientPacketID_GuildRejectAlliance = 50,
    ClientPacketID_GuildRejectPeace = 51,
    ClientPacketID_GuildAcceptAlliance = 52,
    ClientPacketID_GuildOfferPeace = 53,
    ClientPacketID_GuildOfferAlliance = 54,
    ClientPacketID_GuildAllianceDetails = 55,
    ClientPacketID_GuildPeaceDetails = 56,
    ClientPacketID_GuildRequestJoinerInfo = 57,
    ClientPacketID_GuildAlliancePropList = 58,
    ClientPacketID_GuildPeacePropList = 59,
    ClientPacketID_GuildDeclareWar = 60,
    ClientPacketID_GuildNewWebsite = 61,
    ClientPacketID_GuildAcceptNewMember = 62,
    ClientPacketID_GuildRejectNewMember = 63,
    ClientPacketID_GuildKickMember = 64,
    ClientPacketID_GuildUpdateNews = 65,
    ClientPacketID_GuildMemberInfo = 66,
    ClientPacketID_GuildOpenElections = 67,
    ClientPacketID_GuildRequestMembership = 68,
    ClientPacketID_GuildRequestDetails = 69,
    ClientPacketID_Online = 70,
    ClientPacketID_Quit = 71,
    ClientPacketID_GuildLeave = 72,
    ClientPacketID_RequestAccountState = 73,
    ClientPacketID_PetStand = 74,
    ClientPacketID_PetFollow = 75,
    ClientPacketID_ReleasePet = 76,
    ClientPacketID_TrainList = 77,
    ClientPacketID_Rest = 78,
    ClientPacketID_Meditate = 79,
    ClientPacketID_Resucitate = 80,
    ClientPacketID_Heal = 81,
    ClientPacketID_Help = 82,
    ClientPacketID_RequestStats = 83,
    ClientPacketID_CommerceStart = 84,
    ClientPacketID_BankStart = 85,
    ClientPacketID_Enlist = 86,
    ClientPacketID_Information = 87,
    ClientPacketID_Reward = 88,
    ClientPacketID_RequestMOTD = 89,
    ClientPacketID_UpTime = 90,
    ClientPacketID_PartyLeave = 91,
    ClientPacketID_PartyCreate = 92,
    ClientPacketID_PartyJoin = 93,
    ClientPacketID_Inquiry = 94,
    ClientPacketID_GuildMessage = 95,
    ClientPacketID_PartyMessage = 96,
    ClientPacketID_CentinelReport = 97,
    ClientPacketID_GuildOnline = 98,
    ClientPacketID_PartyOnline = 99,
    ClientPacketID_CouncilMessage = 100,
    ClientPacketID_RoleMasterRequest = 101,
    ClientPacketID_GMRequest = 102,
    ClientPacketID_BugReport = 103,
    ClientPacketID_ChangeDescription = 104,
    ClientPacketID_GuildVote = 105,
    ClientPacketID_Punishments = 106,
    ClientPacketID_ChangePassword = 107,
    ClientPacketID_Gamble = 108,
    ClientPacketID_InquiryVote = 109,
    ClientPacketID_LeaveFaction = 110,
    ClientPacketID_BankExtractGold = 111,
    ClientPacketID_BankDepositGold = 112,
    ClientPacketID_Denounce = 113,
    ClientPacketID_GuildFundate = 114,
    ClientPacketID_GuildFundation = 115,
    ClientPacketID_PartyKick = 116,
    ClientPacketID_PartySetLeader = 117,
    ClientPacketID_PartyAcceptMember = 118,
    ClientPacketID_Ping = 119,
    ClientPacketID_RequestPartyForm = 120,
    ClientPacketID_ItemUpgrade = 121,
    ClientPacketID_GMCommands = 122,
    ClientPacketID_InitCrafting = 123,
    ClientPacketID_Home = 124,
    ClientPacketID_ShowGuildNews = 125,
    ClientPacketID_ShareNpc = 126,
    ClientPacketID_StopSharingNpc = 127,
    ClientPacketID_Consultation = 128,
    ClientPacketID_MoveItem = 129,
    ClientPacketID_PACKET_COUNT = 130
};

class ClientPacket : public Packet {
public:
    explicit ClientPacket(int id) : Packet(id) { }
};

ClientPacket* ClientPacketFactory(clsByteQueue* buffer);

void ClientPacketDecodeAndDispatch(clsByteQueue* buffer, PacketHandler* handler);


class LoginExistingChar : public ClientPacket {
public:
    LoginExistingChar();
    LoginExistingChar(clsByteQueue* buffer);
    LoginExistingChar(const std::string& UserName, const std::string& Password, std::uint8_t VerA, std::uint8_t VerB, std::uint8_t VerC);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::string Password; 
    std::uint8_t VerA; 
    std::uint8_t VerB; 
    std::uint8_t VerC; 
};

inline LoginExistingChar BuildLoginExistingChar(const std::string& UserName, const std::string& Password, std::uint8_t VerA, std::uint8_t VerB, std::uint8_t VerC) {
    return LoginExistingChar(UserName, Password, VerA, VerB, VerC);
}

class ThrowDices : public ClientPacket {
public:
    ThrowDices();
    ThrowDices(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ThrowDices BuildThrowDices() {
    return ThrowDices();
}

class LoginNewChar : public ClientPacket {
public:
    LoginNewChar();
    LoginNewChar(clsByteQueue* buffer);
    LoginNewChar(const std::string& UserName, const std::string& Password, std::uint8_t VerA, std::uint8_t VerB, std::uint8_t VerC, std::uint8_t Race, std::uint8_t Gender, std::uint8_t Class, std::int16_t Head, const std::string& Mail, std::uint8_t Homeland);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::string Password; 
    std::uint8_t VerA; 
    std::uint8_t VerB; 
    std::uint8_t VerC; 
    std::uint8_t Race; 
    std::uint8_t Gender; 
    std::uint8_t Class; 
    std::int16_t Head; 
    std::string Mail; 
    std::uint8_t Homeland; 
};

inline LoginNewChar BuildLoginNewChar(const std::string& UserName, const std::string& Password, std::uint8_t VerA, std::uint8_t VerB, std::uint8_t VerC, std::uint8_t Race, std::uint8_t Gender, std::uint8_t Class, std::int16_t Head, const std::string& Mail, std::uint8_t Homeland) {
    return LoginNewChar(UserName, Password, VerA, VerB, VerC, Race, Gender, Class, Head, Mail, Homeland);
}

class Talk : public ClientPacket {
public:
    Talk();
    Talk(clsByteQueue* buffer);
    Talk(const std::string& Chat);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Chat; 
};

inline Talk BuildTalk(const std::string& Chat) {
    return Talk(Chat);
}

class Yell : public ClientPacket {
public:
    Yell();
    Yell(clsByteQueue* buffer);
    Yell(const std::string& Chat);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Chat; 
};

inline Yell BuildYell(const std::string& Chat) {
    return Yell(Chat);
}

class Whisper : public ClientPacket {
public:
    Whisper();
    Whisper(clsByteQueue* buffer);
    Whisper(const std::string& TargetName, const std::string& Chat);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string TargetName; 
    std::string Chat; 
};

inline Whisper BuildWhisper(const std::string& TargetName, const std::string& Chat) {
    return Whisper(TargetName, Chat);
}

class Walk : public ClientPacket {
public:
    Walk();
    Walk(clsByteQueue* buffer);
    Walk(std::uint8_t Heading);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Heading; 
};

inline Walk BuildWalk(std::uint8_t Heading) {
    return Walk(Heading);
}

class RequestPositionUpdate : public ClientPacket {
public:
    RequestPositionUpdate();
    RequestPositionUpdate(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RequestPositionUpdate BuildRequestPositionUpdate() {
    return RequestPositionUpdate();
}

class Attack : public ClientPacket {
public:
    Attack();
    Attack(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Attack BuildAttack() {
    return Attack();
}

class PickUp : public ClientPacket {
public:
    PickUp();
    PickUp(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline PickUp BuildPickUp() {
    return PickUp();
}

class SafeToggle : public ClientPacket {
public:
    SafeToggle();
    SafeToggle(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline SafeToggle BuildSafeToggle() {
    return SafeToggle();
}

class ResuscitationSafeToggle : public ClientPacket {
public:
    ResuscitationSafeToggle();
    ResuscitationSafeToggle(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ResuscitationSafeToggle BuildResuscitationSafeToggle() {
    return ResuscitationSafeToggle();
}

class RequestGuildLeaderInfo : public ClientPacket {
public:
    RequestGuildLeaderInfo();
    RequestGuildLeaderInfo(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RequestGuildLeaderInfo BuildRequestGuildLeaderInfo() {
    return RequestGuildLeaderInfo();
}

class RequestAtributes : public ClientPacket {
public:
    RequestAtributes();
    RequestAtributes(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RequestAtributes BuildRequestAtributes() {
    return RequestAtributes();
}

class RequestFame : public ClientPacket {
public:
    RequestFame();
    RequestFame(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RequestFame BuildRequestFame() {
    return RequestFame();
}

class RequestSkills : public ClientPacket {
public:
    RequestSkills();
    RequestSkills(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RequestSkills BuildRequestSkills() {
    return RequestSkills();
}

class RequestMiniStats : public ClientPacket {
public:
    RequestMiniStats();
    RequestMiniStats(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RequestMiniStats BuildRequestMiniStats() {
    return RequestMiniStats();
}

class CommerceEnd : public ClientPacket {
public:
    CommerceEnd();
    CommerceEnd(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline CommerceEnd BuildCommerceEnd() {
    return CommerceEnd();
}

class UserCommerceEnd : public ClientPacket {
public:
    UserCommerceEnd();
    UserCommerceEnd(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline UserCommerceEnd BuildUserCommerceEnd() {
    return UserCommerceEnd();
}

class UserCommerceConfirm : public ClientPacket {
public:
    UserCommerceConfirm();
    UserCommerceConfirm(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline UserCommerceConfirm BuildUserCommerceConfirm() {
    return UserCommerceConfirm();
}

class CommerceChat : public ClientPacket {
public:
    CommerceChat();
    CommerceChat(clsByteQueue* buffer);
    CommerceChat(const std::string& Chat);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Chat; 
};

inline CommerceChat BuildCommerceChat(const std::string& Chat) {
    return CommerceChat(Chat);
}

class BankEnd : public ClientPacket {
public:
    BankEnd();
    BankEnd(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline BankEnd BuildBankEnd() {
    return BankEnd();
}

class UserCommerceOk : public ClientPacket {
public:
    UserCommerceOk();
    UserCommerceOk(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline UserCommerceOk BuildUserCommerceOk() {
    return UserCommerceOk();
}

class UserCommerceReject : public ClientPacket {
public:
    UserCommerceReject();
    UserCommerceReject(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline UserCommerceReject BuildUserCommerceReject() {
    return UserCommerceReject();
}

class Drop : public ClientPacket {
public:
    Drop();
    Drop(clsByteQueue* buffer);
    Drop(std::uint8_t Slot, std::int16_t Amount);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Slot; 
    std::int16_t Amount; 
};

inline Drop BuildDrop(std::uint8_t Slot, std::int16_t Amount) {
    return Drop(Slot, Amount);
}

class CastSpell : public ClientPacket {
public:
    CastSpell();
    CastSpell(clsByteQueue* buffer);
    CastSpell(std::uint8_t Spell);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Spell; 
};

inline CastSpell BuildCastSpell(std::uint8_t Spell) {
    return CastSpell(Spell);
}

class LeftClick : public ClientPacket {
public:
    LeftClick();
    LeftClick(clsByteQueue* buffer);
    LeftClick(std::uint8_t X, std::uint8_t Y);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t X; 
    std::uint8_t Y; 
};

inline LeftClick BuildLeftClick(std::uint8_t X, std::uint8_t Y) {
    return LeftClick(X, Y);
}

class DoubleClick : public ClientPacket {
public:
    DoubleClick();
    DoubleClick(clsByteQueue* buffer);
    DoubleClick(std::uint8_t X, std::uint8_t Y);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t X; 
    std::uint8_t Y; 
};

inline DoubleClick BuildDoubleClick(std::uint8_t X, std::uint8_t Y) {
    return DoubleClick(X, Y);
}

class Work : public ClientPacket {
public:
    Work();
    Work(clsByteQueue* buffer);
    Work(std::uint8_t Skill);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Skill; 
};

inline Work BuildWork(std::uint8_t Skill) {
    return Work(Skill);
}

class UseSpellMacro : public ClientPacket {
public:
    UseSpellMacro();
    UseSpellMacro(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline UseSpellMacro BuildUseSpellMacro() {
    return UseSpellMacro();
}

class UseItem : public ClientPacket {
public:
    UseItem();
    UseItem(clsByteQueue* buffer);
    UseItem(std::uint8_t Slot);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Slot; 
};

inline UseItem BuildUseItem(std::uint8_t Slot) {
    return UseItem(Slot);
}

class CraftBlacksmith : public ClientPacket {
public:
    CraftBlacksmith();
    CraftBlacksmith(clsByteQueue* buffer);
    CraftBlacksmith(std::int16_t Item);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t Item; 
};

inline CraftBlacksmith BuildCraftBlacksmith(std::int16_t Item) {
    return CraftBlacksmith(Item);
}

class CraftCarpenter : public ClientPacket {
public:
    CraftCarpenter();
    CraftCarpenter(clsByteQueue* buffer);
    CraftCarpenter(std::int16_t Item);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t Item; 
};

inline CraftCarpenter BuildCraftCarpenter(std::int16_t Item) {
    return CraftCarpenter(Item);
}

class WorkLeftClick : public ClientPacket {
public:
    WorkLeftClick();
    WorkLeftClick(clsByteQueue* buffer);
    WorkLeftClick(std::uint8_t X, std::uint8_t Y, std::uint8_t Skill);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t X; 
    std::uint8_t Y; 
    std::uint8_t Skill; 
};

inline WorkLeftClick BuildWorkLeftClick(std::uint8_t X, std::uint8_t Y, std::uint8_t Skill) {
    return WorkLeftClick(X, Y, Skill);
}

class CreateNewGuild : public ClientPacket {
public:
    CreateNewGuild();
    CreateNewGuild(clsByteQueue* buffer);
    CreateNewGuild(const std::string& Desc, const std::string& GuildName, const std::string& Site, const std::string& Codex);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Desc; 
    std::string GuildName; 
    std::string Site; 
    std::string Codex; 
};

inline CreateNewGuild BuildCreateNewGuild(const std::string& Desc, const std::string& GuildName, const std::string& Site, const std::string& Codex) {
    return CreateNewGuild(Desc, GuildName, Site, Codex);
}

class SpellInfo : public ClientPacket {
public:
    SpellInfo();
    SpellInfo(clsByteQueue* buffer);
    SpellInfo(std::uint8_t Slot);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Slot; 
};

inline SpellInfo BuildSpellInfo(std::uint8_t Slot) {
    return SpellInfo(Slot);
}

class EquipItem : public ClientPacket {
public:
    EquipItem();
    EquipItem(clsByteQueue* buffer);
    EquipItem(std::uint8_t Slot);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Slot; 
};

inline EquipItem BuildEquipItem(std::uint8_t Slot) {
    return EquipItem(Slot);
}

class ChangeHeading : public ClientPacket {
public:
    ChangeHeading();
    ChangeHeading(clsByteQueue* buffer);
    ChangeHeading(std::uint8_t Heading);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Heading; 
};

inline ChangeHeading BuildChangeHeading(std::uint8_t Heading) {
    return ChangeHeading(Heading);
}

class ModifySkills : public ClientPacket {
public:
    ModifySkills();
    ModifySkills(clsByteQueue* buffer);
    ModifySkills(std::vector<std::uint8_t> Skills );

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::vector<std::uint8_t> Skills; 
};

inline ModifySkills BuildModifySkills(std::vector<std::uint8_t> Skills ) {
    return ModifySkills(Skills);
}

class Train : public ClientPacket {
public:
    Train();
    Train(clsByteQueue* buffer);
    Train(std::uint8_t PetIndex);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t PetIndex; 
};

inline Train BuildTrain(std::uint8_t PetIndex) {
    return Train(PetIndex);
}

class CommerceBuy : public ClientPacket {
public:
    CommerceBuy();
    CommerceBuy(clsByteQueue* buffer);
    CommerceBuy(std::uint8_t Slot, std::int16_t Amount);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Slot; 
    std::int16_t Amount; 
};

inline CommerceBuy BuildCommerceBuy(std::uint8_t Slot, std::int16_t Amount) {
    return CommerceBuy(Slot, Amount);
}

class BankExtractItem : public ClientPacket {
public:
    BankExtractItem();
    BankExtractItem(clsByteQueue* buffer);
    BankExtractItem(std::uint8_t Slot, std::int16_t Amount);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Slot; 
    std::int16_t Amount; 
};

inline BankExtractItem BuildBankExtractItem(std::uint8_t Slot, std::int16_t Amount) {
    return BankExtractItem(Slot, Amount);
}

class CommerceSell : public ClientPacket {
public:
    CommerceSell();
    CommerceSell(clsByteQueue* buffer);
    CommerceSell(std::uint8_t Slot, std::int16_t Amount);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Slot; 
    std::int16_t Amount; 
};

inline CommerceSell BuildCommerceSell(std::uint8_t Slot, std::int16_t Amount) {
    return CommerceSell(Slot, Amount);
}

class BankDeposit : public ClientPacket {
public:
    BankDeposit();
    BankDeposit(clsByteQueue* buffer);
    BankDeposit(std::uint8_t Slot, std::int16_t Amount);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Slot; 
    std::int16_t Amount; 
};

inline BankDeposit BuildBankDeposit(std::uint8_t Slot, std::int16_t Amount) {
    return BankDeposit(Slot, Amount);
}

class ForumPost : public ClientPacket {
public:
    ForumPost();
    ForumPost(clsByteQueue* buffer);
    ForumPost(std::uint8_t MsgType, const std::string& Title, const std::string& Post);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t MsgType; 
    std::string Title; 
    std::string Post; 
};

inline ForumPost BuildForumPost(std::uint8_t MsgType, const std::string& Title, const std::string& Post) {
    return ForumPost(MsgType, Title, Post);
}

class MoveSpell : public ClientPacket {
public:
    MoveSpell();
    MoveSpell(clsByteQueue* buffer);
    MoveSpell(bool Direction, std::uint8_t Slot);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    bool Direction; 
    std::uint8_t Slot; 
};

inline MoveSpell BuildMoveSpell(bool Direction, std::uint8_t Slot) {
    return MoveSpell(Direction, Slot);
}

class MoveBank : public ClientPacket {
public:
    MoveBank();
    MoveBank(clsByteQueue* buffer);
    MoveBank(bool Direction, std::uint8_t Slot);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    bool Direction; 
    std::uint8_t Slot; 
};

inline MoveBank BuildMoveBank(bool Direction, std::uint8_t Slot) {
    return MoveBank(Direction, Slot);
}

class ClanCodexUpdate : public ClientPacket {
public:
    ClanCodexUpdate();
    ClanCodexUpdate(clsByteQueue* buffer);
    ClanCodexUpdate(const std::string& Desc, const std::string& Codex);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Desc; 
    std::string Codex; 
};

inline ClanCodexUpdate BuildClanCodexUpdate(const std::string& Desc, const std::string& Codex) {
    return ClanCodexUpdate(Desc, Codex);
}

class UserCommerceOffer : public ClientPacket {
public:
    UserCommerceOffer();
    UserCommerceOffer(clsByteQueue* buffer);
    UserCommerceOffer(std::uint8_t Slot, std::int32_t Amount, std::uint8_t OfferSlot);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Slot; 
    std::int32_t Amount; 
    std::uint8_t OfferSlot; 
};

inline UserCommerceOffer BuildUserCommerceOffer(std::uint8_t Slot, std::int32_t Amount, std::uint8_t OfferSlot) {
    return UserCommerceOffer(Slot, Amount, OfferSlot);
}

class GuildAcceptPeace : public ClientPacket {
public:
    GuildAcceptPeace();
    GuildAcceptPeace(clsByteQueue* buffer);
    GuildAcceptPeace(const std::string& Guild);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Guild; 
};

inline GuildAcceptPeace BuildGuildAcceptPeace(const std::string& Guild) {
    return GuildAcceptPeace(Guild);
}

class GuildRejectAlliance : public ClientPacket {
public:
    GuildRejectAlliance();
    GuildRejectAlliance(clsByteQueue* buffer);
    GuildRejectAlliance(const std::string& Guild);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Guild; 
};

inline GuildRejectAlliance BuildGuildRejectAlliance(const std::string& Guild) {
    return GuildRejectAlliance(Guild);
}

class GuildRejectPeace : public ClientPacket {
public:
    GuildRejectPeace();
    GuildRejectPeace(clsByteQueue* buffer);
    GuildRejectPeace(const std::string& Guild);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Guild; 
};

inline GuildRejectPeace BuildGuildRejectPeace(const std::string& Guild) {
    return GuildRejectPeace(Guild);
}

class GuildAcceptAlliance : public ClientPacket {
public:
    GuildAcceptAlliance();
    GuildAcceptAlliance(clsByteQueue* buffer);
    GuildAcceptAlliance(const std::string& Guild);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Guild; 
};

inline GuildAcceptAlliance BuildGuildAcceptAlliance(const std::string& Guild) {
    return GuildAcceptAlliance(Guild);
}

class GuildOfferPeace : public ClientPacket {
public:
    GuildOfferPeace();
    GuildOfferPeace(clsByteQueue* buffer);
    GuildOfferPeace(const std::string& Guild, const std::string& Proposal);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Guild; 
    std::string Proposal; 
};

inline GuildOfferPeace BuildGuildOfferPeace(const std::string& Guild, const std::string& Proposal) {
    return GuildOfferPeace(Guild, Proposal);
}

class GuildOfferAlliance : public ClientPacket {
public:
    GuildOfferAlliance();
    GuildOfferAlliance(clsByteQueue* buffer);
    GuildOfferAlliance(const std::string& Guild, const std::string& Proposal);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Guild; 
    std::string Proposal; 
};

inline GuildOfferAlliance BuildGuildOfferAlliance(const std::string& Guild, const std::string& Proposal) {
    return GuildOfferAlliance(Guild, Proposal);
}

class GuildAllianceDetails : public ClientPacket {
public:
    GuildAllianceDetails();
    GuildAllianceDetails(clsByteQueue* buffer);
    GuildAllianceDetails(const std::string& Guild);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Guild; 
};

inline GuildAllianceDetails BuildGuildAllianceDetails(const std::string& Guild) {
    return GuildAllianceDetails(Guild);
}

class GuildPeaceDetails : public ClientPacket {
public:
    GuildPeaceDetails();
    GuildPeaceDetails(clsByteQueue* buffer);
    GuildPeaceDetails(const std::string& Guild);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Guild; 
};

inline GuildPeaceDetails BuildGuildPeaceDetails(const std::string& Guild) {
    return GuildPeaceDetails(Guild);
}

class GuildRequestJoinerInfo : public ClientPacket {
public:
    GuildRequestJoinerInfo();
    GuildRequestJoinerInfo(clsByteQueue* buffer);
    GuildRequestJoinerInfo(const std::string& User);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string User; 
};

inline GuildRequestJoinerInfo BuildGuildRequestJoinerInfo(const std::string& User) {
    return GuildRequestJoinerInfo(User);
}

class GuildAlliancePropList : public ClientPacket {
public:
    GuildAlliancePropList();
    GuildAlliancePropList(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline GuildAlliancePropList BuildGuildAlliancePropList() {
    return GuildAlliancePropList();
}

class GuildPeacePropList : public ClientPacket {
public:
    GuildPeacePropList();
    GuildPeacePropList(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline GuildPeacePropList BuildGuildPeacePropList() {
    return GuildPeacePropList();
}

class GuildDeclareWar : public ClientPacket {
public:
    GuildDeclareWar();
    GuildDeclareWar(clsByteQueue* buffer);
    GuildDeclareWar(const std::string& Guild);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Guild; 
};

inline GuildDeclareWar BuildGuildDeclareWar(const std::string& Guild) {
    return GuildDeclareWar(Guild);
}

class GuildNewWebsite : public ClientPacket {
public:
    GuildNewWebsite();
    GuildNewWebsite(clsByteQueue* buffer);
    GuildNewWebsite(const std::string& Website);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Website; 
};

inline GuildNewWebsite BuildGuildNewWebsite(const std::string& Website) {
    return GuildNewWebsite(Website);
}

class GuildAcceptNewMember : public ClientPacket {
public:
    GuildAcceptNewMember();
    GuildAcceptNewMember(clsByteQueue* buffer);
    GuildAcceptNewMember(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline GuildAcceptNewMember BuildGuildAcceptNewMember(const std::string& UserName) {
    return GuildAcceptNewMember(UserName);
}

class GuildRejectNewMember : public ClientPacket {
public:
    GuildRejectNewMember();
    GuildRejectNewMember(clsByteQueue* buffer);
    GuildRejectNewMember(const std::string& UserName, const std::string& Reason);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::string Reason; 
};

inline GuildRejectNewMember BuildGuildRejectNewMember(const std::string& UserName, const std::string& Reason) {
    return GuildRejectNewMember(UserName, Reason);
}

class GuildKickMember : public ClientPacket {
public:
    GuildKickMember();
    GuildKickMember(clsByteQueue* buffer);
    GuildKickMember(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline GuildKickMember BuildGuildKickMember(const std::string& UserName) {
    return GuildKickMember(UserName);
}

class GuildUpdateNews : public ClientPacket {
public:
    GuildUpdateNews();
    GuildUpdateNews(clsByteQueue* buffer);
    GuildUpdateNews(const std::string& News);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string News; 
};

inline GuildUpdateNews BuildGuildUpdateNews(const std::string& News) {
    return GuildUpdateNews(News);
}

class GuildMemberInfo : public ClientPacket {
public:
    GuildMemberInfo();
    GuildMemberInfo(clsByteQueue* buffer);
    GuildMemberInfo(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline GuildMemberInfo BuildGuildMemberInfo(const std::string& UserName) {
    return GuildMemberInfo(UserName);
}

class GuildOpenElections : public ClientPacket {
public:
    GuildOpenElections();
    GuildOpenElections(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline GuildOpenElections BuildGuildOpenElections() {
    return GuildOpenElections();
}

class GuildRequestMembership : public ClientPacket {
public:
    GuildRequestMembership();
    GuildRequestMembership(clsByteQueue* buffer);
    GuildRequestMembership(const std::string& Guild, const std::string& Application);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Guild; 
    std::string Application; 
};

inline GuildRequestMembership BuildGuildRequestMembership(const std::string& Guild, const std::string& Application) {
    return GuildRequestMembership(Guild, Application);
}

class GuildRequestDetails : public ClientPacket {
public:
    GuildRequestDetails();
    GuildRequestDetails(clsByteQueue* buffer);
    GuildRequestDetails(const std::string& Guild);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Guild; 
};

inline GuildRequestDetails BuildGuildRequestDetails(const std::string& Guild) {
    return GuildRequestDetails(Guild);
}

class Online : public ClientPacket {
public:
    Online();
    Online(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Online BuildOnline() {
    return Online();
}

class Quit : public ClientPacket {
public:
    Quit();
    Quit(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Quit BuildQuit() {
    return Quit();
}

class GuildLeave : public ClientPacket {
public:
    GuildLeave();
    GuildLeave(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline GuildLeave BuildGuildLeave() {
    return GuildLeave();
}

class RequestAccountState : public ClientPacket {
public:
    RequestAccountState();
    RequestAccountState(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RequestAccountState BuildRequestAccountState() {
    return RequestAccountState();
}

class PetStand : public ClientPacket {
public:
    PetStand();
    PetStand(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline PetStand BuildPetStand() {
    return PetStand();
}

class PetFollow : public ClientPacket {
public:
    PetFollow();
    PetFollow(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline PetFollow BuildPetFollow() {
    return PetFollow();
}

class ReleasePet : public ClientPacket {
public:
    ReleasePet();
    ReleasePet(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ReleasePet BuildReleasePet() {
    return ReleasePet();
}

class TrainList : public ClientPacket {
public:
    TrainList();
    TrainList(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline TrainList BuildTrainList() {
    return TrainList();
}

class Rest : public ClientPacket {
public:
    Rest();
    Rest(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Rest BuildRest() {
    return Rest();
}

class Meditate : public ClientPacket {
public:
    Meditate();
    Meditate(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Meditate BuildMeditate() {
    return Meditate();
}

class Resucitate : public ClientPacket {
public:
    Resucitate();
    Resucitate(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Resucitate BuildResucitate() {
    return Resucitate();
}

class Heal : public ClientPacket {
public:
    Heal();
    Heal(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Heal BuildHeal() {
    return Heal();
}

class Help : public ClientPacket {
public:
    Help();
    Help(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Help BuildHelp() {
    return Help();
}

class RequestStats : public ClientPacket {
public:
    RequestStats();
    RequestStats(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RequestStats BuildRequestStats() {
    return RequestStats();
}

class CommerceStart : public ClientPacket {
public:
    CommerceStart();
    CommerceStart(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline CommerceStart BuildCommerceStart() {
    return CommerceStart();
}

class BankStart : public ClientPacket {
public:
    BankStart();
    BankStart(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline BankStart BuildBankStart() {
    return BankStart();
}

class Enlist : public ClientPacket {
public:
    Enlist();
    Enlist(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Enlist BuildEnlist() {
    return Enlist();
}

class Information : public ClientPacket {
public:
    Information();
    Information(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Information BuildInformation() {
    return Information();
}

class Reward : public ClientPacket {
public:
    Reward();
    Reward(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Reward BuildReward() {
    return Reward();
}

class RequestMOTD : public ClientPacket {
public:
    RequestMOTD();
    RequestMOTD(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RequestMOTD BuildRequestMOTD() {
    return RequestMOTD();
}

class UpTime : public ClientPacket {
public:
    UpTime();
    UpTime(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline UpTime BuildUpTime() {
    return UpTime();
}

class PartyLeave : public ClientPacket {
public:
    PartyLeave();
    PartyLeave(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline PartyLeave BuildPartyLeave() {
    return PartyLeave();
}

class PartyCreate : public ClientPacket {
public:
    PartyCreate();
    PartyCreate(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline PartyCreate BuildPartyCreate() {
    return PartyCreate();
}

class PartyJoin : public ClientPacket {
public:
    PartyJoin();
    PartyJoin(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline PartyJoin BuildPartyJoin() {
    return PartyJoin();
}

class Inquiry : public ClientPacket {
public:
    Inquiry();
    Inquiry(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Inquiry BuildInquiry() {
    return Inquiry();
}

class GuildMessage : public ClientPacket {
public:
    GuildMessage();
    GuildMessage(clsByteQueue* buffer);
    GuildMessage(const std::string& Chat);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Chat; 
};

inline GuildMessage BuildGuildMessage(const std::string& Chat) {
    return GuildMessage(Chat);
}

class PartyMessage : public ClientPacket {
public:
    PartyMessage();
    PartyMessage(clsByteQueue* buffer);
    PartyMessage(const std::string& Chat);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Chat; 
};

inline PartyMessage BuildPartyMessage(const std::string& Chat) {
    return PartyMessage(Chat);
}

class CentinelReport : public ClientPacket {
public:
    CentinelReport();
    CentinelReport(clsByteQueue* buffer);
    CentinelReport(std::int16_t Code);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t Code; 
};

inline CentinelReport BuildCentinelReport(std::int16_t Code) {
    return CentinelReport(Code);
}

class GuildOnline : public ClientPacket {
public:
    GuildOnline();
    GuildOnline(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline GuildOnline BuildGuildOnline() {
    return GuildOnline();
}

class PartyOnline : public ClientPacket {
public:
    PartyOnline();
    PartyOnline(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline PartyOnline BuildPartyOnline() {
    return PartyOnline();
}

class CouncilMessage : public ClientPacket {
public:
    CouncilMessage();
    CouncilMessage(clsByteQueue* buffer);
    CouncilMessage(const std::string& Chat);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Chat; 
};

inline CouncilMessage BuildCouncilMessage(const std::string& Chat) {
    return CouncilMessage(Chat);
}

class RoleMasterRequest : public ClientPacket {
public:
    RoleMasterRequest();
    RoleMasterRequest(clsByteQueue* buffer);
    RoleMasterRequest(const std::string& Request);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Request; 
};

inline RoleMasterRequest BuildRoleMasterRequest(const std::string& Request) {
    return RoleMasterRequest(Request);
}

class GMRequest : public ClientPacket {
public:
    GMRequest();
    GMRequest(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline GMRequest BuildGMRequest() {
    return GMRequest();
}

class BugReport : public ClientPacket {
public:
    BugReport();
    BugReport(clsByteQueue* buffer);
    BugReport(const std::string& Report);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Report; 
};

inline BugReport BuildBugReport(const std::string& Report) {
    return BugReport(Report);
}

class ChangeDescription : public ClientPacket {
public:
    ChangeDescription();
    ChangeDescription(clsByteQueue* buffer);
    ChangeDescription(const std::string& Description);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Description; 
};

inline ChangeDescription BuildChangeDescription(const std::string& Description) {
    return ChangeDescription(Description);
}

class GuildVote : public ClientPacket {
public:
    GuildVote();
    GuildVote(clsByteQueue* buffer);
    GuildVote(const std::string& Vote);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Vote; 
};

inline GuildVote BuildGuildVote(const std::string& Vote) {
    return GuildVote(Vote);
}

class Punishments : public ClientPacket {
public:
    Punishments();
    Punishments(clsByteQueue* buffer);
    Punishments(const std::string& Name);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Name; 
};

inline Punishments BuildPunishments(const std::string& Name) {
    return Punishments(Name);
}

class ChangePassword : public ClientPacket {
public:
    ChangePassword();
    ChangePassword(clsByteQueue* buffer);
    ChangePassword(const std::string& OldPass, const std::string& NewPass);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string OldPass; 
    std::string NewPass; 
};

inline ChangePassword BuildChangePassword(const std::string& OldPass, const std::string& NewPass) {
    return ChangePassword(OldPass, NewPass);
}

class Gamble : public ClientPacket {
public:
    Gamble();
    Gamble(clsByteQueue* buffer);
    Gamble(std::int16_t Amount);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t Amount; 
};

inline Gamble BuildGamble(std::int16_t Amount) {
    return Gamble(Amount);
}

class InquiryVote : public ClientPacket {
public:
    InquiryVote();
    InquiryVote(clsByteQueue* buffer);
    InquiryVote(std::uint8_t Opt);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Opt; 
};

inline InquiryVote BuildInquiryVote(std::uint8_t Opt) {
    return InquiryVote(Opt);
}

class LeaveFaction : public ClientPacket {
public:
    LeaveFaction();
    LeaveFaction(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline LeaveFaction BuildLeaveFaction() {
    return LeaveFaction();
}

class BankExtractGold : public ClientPacket {
public:
    BankExtractGold();
    BankExtractGold(clsByteQueue* buffer);
    BankExtractGold(std::int32_t Amount);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int32_t Amount; 
};

inline BankExtractGold BuildBankExtractGold(std::int32_t Amount) {
    return BankExtractGold(Amount);
}

class BankDepositGold : public ClientPacket {
public:
    BankDepositGold();
    BankDepositGold(clsByteQueue* buffer);
    BankDepositGold(std::int32_t Amount);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int32_t Amount; 
};

inline BankDepositGold BuildBankDepositGold(std::int32_t Amount) {
    return BankDepositGold(Amount);
}

class Denounce : public ClientPacket {
public:
    Denounce();
    Denounce(clsByteQueue* buffer);
    Denounce(const std::string& Text);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Text; 
};

inline Denounce BuildDenounce(const std::string& Text) {
    return Denounce(Text);
}

class GuildFundate : public ClientPacket {
public:
    GuildFundate();
    GuildFundate(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline GuildFundate BuildGuildFundate() {
    return GuildFundate();
}

class GuildFundation : public ClientPacket {
public:
    GuildFundation();
    GuildFundation(clsByteQueue* buffer);
    GuildFundation(std::uint8_t ClanType);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t ClanType; 
};

inline GuildFundation BuildGuildFundation(std::uint8_t ClanType) {
    return GuildFundation(ClanType);
}

class PartyKick : public ClientPacket {
public:
    PartyKick();
    PartyKick(clsByteQueue* buffer);
    PartyKick(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline PartyKick BuildPartyKick(const std::string& UserName) {
    return PartyKick(UserName);
}

class PartySetLeader : public ClientPacket {
public:
    PartySetLeader();
    PartySetLeader(clsByteQueue* buffer);
    PartySetLeader(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline PartySetLeader BuildPartySetLeader(const std::string& UserName) {
    return PartySetLeader(UserName);
}

class PartyAcceptMember : public ClientPacket {
public:
    PartyAcceptMember();
    PartyAcceptMember(clsByteQueue* buffer);
    PartyAcceptMember(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline PartyAcceptMember BuildPartyAcceptMember(const std::string& UserName) {
    return PartyAcceptMember(UserName);
}

class Ping : public ClientPacket {
public:
    Ping();
    Ping(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Ping BuildPing() {
    return Ping();
}

class RequestPartyForm : public ClientPacket {
public:
    RequestPartyForm();
    RequestPartyForm(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RequestPartyForm BuildRequestPartyForm() {
    return RequestPartyForm();
}

class ItemUpgrade : public ClientPacket {
public:
    ItemUpgrade();
    ItemUpgrade(clsByteQueue* buffer);
    ItemUpgrade(std::int16_t ItemIndex);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t ItemIndex; 
};

inline ItemUpgrade BuildItemUpgrade(std::int16_t ItemIndex) {
    return ItemUpgrade(ItemIndex);
}

class GMCommands : public ClientPacket {
public:
    GMCommands();
    GMCommands(clsByteQueue* buffer);
    virtual ~GMCommands();

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::unique_ptr<dakara::protocol::clientgm::ClientGMPacket> composite;

};

class InitCrafting : public ClientPacket {
public:
    InitCrafting();
    InitCrafting(clsByteQueue* buffer);
    InitCrafting(std::int32_t TotalItems, std::int16_t ItemsPorCiclo);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int32_t TotalItems; 
    std::int16_t ItemsPorCiclo; 
};

inline InitCrafting BuildInitCrafting(std::int32_t TotalItems, std::int16_t ItemsPorCiclo) {
    return InitCrafting(TotalItems, ItemsPorCiclo);
}

class Home : public ClientPacket {
public:
    Home();
    Home(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Home BuildHome() {
    return Home();
}

class ShowGuildNews : public ClientPacket {
public:
    ShowGuildNews();
    ShowGuildNews(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ShowGuildNews BuildShowGuildNews() {
    return ShowGuildNews();
}

class ShareNpc : public ClientPacket {
public:
    ShareNpc();
    ShareNpc(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ShareNpc BuildShareNpc() {
    return ShareNpc();
}

class StopSharingNpc : public ClientPacket {
public:
    StopSharingNpc();
    StopSharingNpc(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline StopSharingNpc BuildStopSharingNpc() {
    return StopSharingNpc();
}

class Consultation : public ClientPacket {
public:
    Consultation();
    Consultation(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Consultation BuildConsultation() {
    return Consultation();
}

class MoveItem : public ClientPacket {
public:
    MoveItem();
    MoveItem(clsByteQueue* buffer);
    MoveItem(std::uint8_t OldSlot, std::uint8_t NewSlot);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t OldSlot; 
    std::uint8_t NewSlot; 
};

inline MoveItem BuildMoveItem(std::uint8_t OldSlot, std::uint8_t NewSlot) {
    return MoveItem(OldSlot, NewSlot);
}

class ClientPacketHandler {
public:
    virtual ~ClientPacketHandler();

    virtual void handleLoginExistingChar(LoginExistingChar* p);
    virtual void handleThrowDices(ThrowDices* p);
    virtual void handleLoginNewChar(LoginNewChar* p);
    virtual void handleTalk(Talk* p);
    virtual void handleYell(Yell* p);
    virtual void handleWhisper(Whisper* p);
    virtual void handleWalk(Walk* p);
    virtual void handleRequestPositionUpdate(RequestPositionUpdate* p);
    virtual void handleAttack(Attack* p);
    virtual void handlePickUp(PickUp* p);
    virtual void handleSafeToggle(SafeToggle* p);
    virtual void handleResuscitationSafeToggle(ResuscitationSafeToggle* p);
    virtual void handleRequestGuildLeaderInfo(RequestGuildLeaderInfo* p);
    virtual void handleRequestAtributes(RequestAtributes* p);
    virtual void handleRequestFame(RequestFame* p);
    virtual void handleRequestSkills(RequestSkills* p);
    virtual void handleRequestMiniStats(RequestMiniStats* p);
    virtual void handleCommerceEnd(CommerceEnd* p);
    virtual void handleUserCommerceEnd(UserCommerceEnd* p);
    virtual void handleUserCommerceConfirm(UserCommerceConfirm* p);
    virtual void handleCommerceChat(CommerceChat* p);
    virtual void handleBankEnd(BankEnd* p);
    virtual void handleUserCommerceOk(UserCommerceOk* p);
    virtual void handleUserCommerceReject(UserCommerceReject* p);
    virtual void handleDrop(Drop* p);
    virtual void handleCastSpell(CastSpell* p);
    virtual void handleLeftClick(LeftClick* p);
    virtual void handleDoubleClick(DoubleClick* p);
    virtual void handleWork(Work* p);
    virtual void handleUseSpellMacro(UseSpellMacro* p);
    virtual void handleUseItem(UseItem* p);
    virtual void handleCraftBlacksmith(CraftBlacksmith* p);
    virtual void handleCraftCarpenter(CraftCarpenter* p);
    virtual void handleWorkLeftClick(WorkLeftClick* p);
    virtual void handleCreateNewGuild(CreateNewGuild* p);
    virtual void handleSpellInfo(SpellInfo* p);
    virtual void handleEquipItem(EquipItem* p);
    virtual void handleChangeHeading(ChangeHeading* p);
    virtual void handleModifySkills(ModifySkills* p);
    virtual void handleTrain(Train* p);
    virtual void handleCommerceBuy(CommerceBuy* p);
    virtual void handleBankExtractItem(BankExtractItem* p);
    virtual void handleCommerceSell(CommerceSell* p);
    virtual void handleBankDeposit(BankDeposit* p);
    virtual void handleForumPost(ForumPost* p);
    virtual void handleMoveSpell(MoveSpell* p);
    virtual void handleMoveBank(MoveBank* p);
    virtual void handleClanCodexUpdate(ClanCodexUpdate* p);
    virtual void handleUserCommerceOffer(UserCommerceOffer* p);
    virtual void handleGuildAcceptPeace(GuildAcceptPeace* p);
    virtual void handleGuildRejectAlliance(GuildRejectAlliance* p);
    virtual void handleGuildRejectPeace(GuildRejectPeace* p);
    virtual void handleGuildAcceptAlliance(GuildAcceptAlliance* p);
    virtual void handleGuildOfferPeace(GuildOfferPeace* p);
    virtual void handleGuildOfferAlliance(GuildOfferAlliance* p);
    virtual void handleGuildAllianceDetails(GuildAllianceDetails* p);
    virtual void handleGuildPeaceDetails(GuildPeaceDetails* p);
    virtual void handleGuildRequestJoinerInfo(GuildRequestJoinerInfo* p);
    virtual void handleGuildAlliancePropList(GuildAlliancePropList* p);
    virtual void handleGuildPeacePropList(GuildPeacePropList* p);
    virtual void handleGuildDeclareWar(GuildDeclareWar* p);
    virtual void handleGuildNewWebsite(GuildNewWebsite* p);
    virtual void handleGuildAcceptNewMember(GuildAcceptNewMember* p);
    virtual void handleGuildRejectNewMember(GuildRejectNewMember* p);
    virtual void handleGuildKickMember(GuildKickMember* p);
    virtual void handleGuildUpdateNews(GuildUpdateNews* p);
    virtual void handleGuildMemberInfo(GuildMemberInfo* p);
    virtual void handleGuildOpenElections(GuildOpenElections* p);
    virtual void handleGuildRequestMembership(GuildRequestMembership* p);
    virtual void handleGuildRequestDetails(GuildRequestDetails* p);
    virtual void handleOnline(Online* p);
    virtual void handleQuit(Quit* p);
    virtual void handleGuildLeave(GuildLeave* p);
    virtual void handleRequestAccountState(RequestAccountState* p);
    virtual void handlePetStand(PetStand* p);
    virtual void handlePetFollow(PetFollow* p);
    virtual void handleReleasePet(ReleasePet* p);
    virtual void handleTrainList(TrainList* p);
    virtual void handleRest(Rest* p);
    virtual void handleMeditate(Meditate* p);
    virtual void handleResucitate(Resucitate* p);
    virtual void handleHeal(Heal* p);
    virtual void handleHelp(Help* p);
    virtual void handleRequestStats(RequestStats* p);
    virtual void handleCommerceStart(CommerceStart* p);
    virtual void handleBankStart(BankStart* p);
    virtual void handleEnlist(Enlist* p);
    virtual void handleInformation(Information* p);
    virtual void handleReward(Reward* p);
    virtual void handleRequestMOTD(RequestMOTD* p);
    virtual void handleUpTime(UpTime* p);
    virtual void handlePartyLeave(PartyLeave* p);
    virtual void handlePartyCreate(PartyCreate* p);
    virtual void handlePartyJoin(PartyJoin* p);
    virtual void handleInquiry(Inquiry* p);
    virtual void handleGuildMessage(GuildMessage* p);
    virtual void handlePartyMessage(PartyMessage* p);
    virtual void handleCentinelReport(CentinelReport* p);
    virtual void handleGuildOnline(GuildOnline* p);
    virtual void handlePartyOnline(PartyOnline* p);
    virtual void handleCouncilMessage(CouncilMessage* p);
    virtual void handleRoleMasterRequest(RoleMasterRequest* p);
    virtual void handleGMRequest(GMRequest* p);
    virtual void handleBugReport(BugReport* p);
    virtual void handleChangeDescription(ChangeDescription* p);
    virtual void handleGuildVote(GuildVote* p);
    virtual void handlePunishments(Punishments* p);
    virtual void handleChangePassword(ChangePassword* p);
    virtual void handleGamble(Gamble* p);
    virtual void handleInquiryVote(InquiryVote* p);
    virtual void handleLeaveFaction(LeaveFaction* p);
    virtual void handleBankExtractGold(BankExtractGold* p);
    virtual void handleBankDepositGold(BankDepositGold* p);
    virtual void handleDenounce(Denounce* p);
    virtual void handleGuildFundate(GuildFundate* p);
    virtual void handleGuildFundation(GuildFundation* p);
    virtual void handlePartyKick(PartyKick* p);
    virtual void handlePartySetLeader(PartySetLeader* p);
    virtual void handlePartyAcceptMember(PartyAcceptMember* p);
    virtual void handlePing(Ping* p);
    virtual void handleRequestPartyForm(RequestPartyForm* p);
    virtual void handleItemUpgrade(ItemUpgrade* p);
    virtual void handleGMCommands(GMCommands* p);
    virtual void handleInitCrafting(InitCrafting* p);
    virtual void handleHome(Home* p);
    virtual void handleShowGuildNews(ShowGuildNews* p);
    virtual void handleShareNpc(ShareNpc* p);
    virtual void handleStopSharingNpc(StopSharingNpc* p);
    virtual void handleConsultation(Consultation* p);
    virtual void handleMoveItem(MoveItem* p);

};

}

namespace clientgm {
enum ClientGMPacketID { 
    ClientGMPacketID_GMMessage = 1,
    ClientGMPacketID_ShowName = 2,
    ClientGMPacketID_OnlineRoyalArmy = 3,
    ClientGMPacketID_OnlineChaosLegion = 4,
    ClientGMPacketID_GoNearby = 5,
    ClientGMPacketID_Comment = 6,
    ClientGMPacketID_ServerTime = 7,
    ClientGMPacketID_Where = 8,
    ClientGMPacketID_CreaturesInMap = 9,
    ClientGMPacketID_WarpMeToTarget = 10,
    ClientGMPacketID_WarpChar = 11,
    ClientGMPacketID_Silence = 12,
    ClientGMPacketID_SOSShowList = 13,
    ClientGMPacketID_SOSRemove = 14,
    ClientGMPacketID_GoToChar = 15,
    ClientGMPacketID_Invisible = 16,
    ClientGMPacketID_GMPanel = 17,
    ClientGMPacketID_RequestUserList = 18,
    ClientGMPacketID_Working = 19,
    ClientGMPacketID_Hiding = 20,
    ClientGMPacketID_Jail = 21,
    ClientGMPacketID_KillNPC = 22,
    ClientGMPacketID_WarnUser = 23,
    ClientGMPacketID_EditChar = 24,
    ClientGMPacketID_RequestCharInfo = 25,
    ClientGMPacketID_RequestCharStats = 26,
    ClientGMPacketID_RequestCharGold = 27,
    ClientGMPacketID_RequestCharInventory = 28,
    ClientGMPacketID_RequestCharBank = 29,
    ClientGMPacketID_RequestCharSkills = 30,
    ClientGMPacketID_ReviveChar = 31,
    ClientGMPacketID_OnlineGM = 32,
    ClientGMPacketID_OnlineMap = 33,
    ClientGMPacketID_Forgive = 34,
    ClientGMPacketID_Kick = 35,
    ClientGMPacketID_Execute = 36,
    ClientGMPacketID_BanChar = 37,
    ClientGMPacketID_UnbanChar = 38,
    ClientGMPacketID_NPCFollow = 39,
    ClientGMPacketID_SummonChar = 40,
    ClientGMPacketID_SpawnListRequest = 41,
    ClientGMPacketID_SpawnCreature = 42,
    ClientGMPacketID_ResetNPCInventory = 43,
    ClientGMPacketID_CleanWorld = 44,
    ClientGMPacketID_ServerMessage = 45,
    ClientGMPacketID_NickToIP = 46,
    ClientGMPacketID_IPToNick = 47,
    ClientGMPacketID_GuildOnlineMembers = 48,
    ClientGMPacketID_TeleportCreate = 49,
    ClientGMPacketID_TeleportDestroy = 50,
    ClientGMPacketID_RainToggle = 51,
    ClientGMPacketID_SetCharDescription = 52,
    ClientGMPacketID_ForceMIDIToMap = 53,
    ClientGMPacketID_ForceWAVEToMap = 54,
    ClientGMPacketID_RoyalArmyMessage = 55,
    ClientGMPacketID_ChaosLegionMessage = 56,
    ClientGMPacketID_CitizenMessage = 57,
    ClientGMPacketID_CriminalMessage = 58,
    ClientGMPacketID_TalkAsNPC = 59,
    ClientGMPacketID_DestroyAllItemsInArea = 60,
    ClientGMPacketID_AcceptRoyalCouncilMember = 61,
    ClientGMPacketID_AcceptChaosCouncilMember = 62,
    ClientGMPacketID_ItemsInTheFloor = 63,
    ClientGMPacketID_MakeDumb = 64,
    ClientGMPacketID_MakeDumbNoMore = 65,
    ClientGMPacketID_DumpIPTables = 66,
    ClientGMPacketID_CouncilKick = 67,
    ClientGMPacketID_SetTrigger = 68,
    ClientGMPacketID_AskTrigger = 69,
    ClientGMPacketID_BannedIPList = 70,
    ClientGMPacketID_BannedIPReload = 71,
    ClientGMPacketID_GuildMemberList = 72,
    ClientGMPacketID_GuildBan = 73,
    ClientGMPacketID_BanIP = 74,
    ClientGMPacketID_UnbanIP = 75,
    ClientGMPacketID_CreateItem = 76,
    ClientGMPacketID_DestroyItems = 77,
    ClientGMPacketID_ChaosLegionKick = 78,
    ClientGMPacketID_RoyalArmyKick = 79,
    ClientGMPacketID_ForceMIDIAll = 80,
    ClientGMPacketID_ForceWAVEAll = 81,
    ClientGMPacketID_RemovePunishment = 82,
    ClientGMPacketID_TileBlockedToggle = 83,
    ClientGMPacketID_KillNPCNoRespawn = 84,
    ClientGMPacketID_KillAllNearbyNPCs = 85,
    ClientGMPacketID_LastIP = 86,
    ClientGMPacketID_ChangeMOTD = 87,
    ClientGMPacketID_SetMOTD = 88,
    ClientGMPacketID_SystemMessage = 89,
    ClientGMPacketID_CreateNPC = 90,
    ClientGMPacketID_CreateNPCWithRespawn = 91,
    ClientGMPacketID_ImperialArmour = 92,
    ClientGMPacketID_ChaosArmour = 93,
    ClientGMPacketID_NavigateToggle = 94,
    ClientGMPacketID_ServerOpenToUsersToggle = 95,
    ClientGMPacketID_TurnOffServer = 96,
    ClientGMPacketID_TurnCriminal = 97,
    ClientGMPacketID_ResetFactions = 98,
    ClientGMPacketID_RemoveCharFromGuild = 99,
    ClientGMPacketID_RequestCharMail = 100,
    ClientGMPacketID_AlterPassword = 101,
    ClientGMPacketID_AlterMail = 102,
    ClientGMPacketID_AlterName = 103,
    ClientGMPacketID_ToggleCentinelActivated = 104,
    ClientGMPacketID_DoBackUp = 105,
    ClientGMPacketID_ShowGuildMessages = 106,
    ClientGMPacketID_SaveMap = 107,
    ClientGMPacketID_ChangeMapInfoPK = 108,
    ClientGMPacketID_ChangeMapInfoBackup = 109,
    ClientGMPacketID_ChangeMapInfoRestricted = 110,
    ClientGMPacketID_ChangeMapInfoNoMagic = 111,
    ClientGMPacketID_ChangeMapInfoNoInvi = 112,
    ClientGMPacketID_ChangeMapInfoNoResu = 113,
    ClientGMPacketID_ChangeMapInfoLand = 114,
    ClientGMPacketID_ChangeMapInfoZone = 115,
    ClientGMPacketID_ChangeMapInfoStealNpc = 116,
    ClientGMPacketID_ChangeMapInfoNoOcultar = 117,
    ClientGMPacketID_ChangeMapInfoNoInvocar = 118,
    ClientGMPacketID_SaveChars = 119,
    ClientGMPacketID_CleanSOS = 120,
    ClientGMPacketID_ShowServerForm = 121,
    ClientGMPacketID_Night = 122,
    ClientGMPacketID_KickAllChars = 123,
    ClientGMPacketID_ReloadNPCs = 124,
    ClientGMPacketID_ReloadServerIni = 125,
    ClientGMPacketID_ReloadSpells = 126,
    ClientGMPacketID_ReloadObjects = 127,
    ClientGMPacketID_Restart = 128,
    ClientGMPacketID_ResetAutoUpdate = 129,
    ClientGMPacketID_ChatColor = 130,
    ClientGMPacketID_Ignored = 131,
    ClientGMPacketID_CheckSlot = 132,
    ClientGMPacketID_SetIniVar = 133,
    ClientGMPacketID_CreatePretorianClan = 134,
    ClientGMPacketID_RemovePretorianClan = 135,
    ClientGMPacketID_EnableDenounces = 136,
    ClientGMPacketID_ShowDenouncesList = 137,
    ClientGMPacketID_MapMessage = 138,
    ClientGMPacketID_SetDialog = 139,
    ClientGMPacketID_Impersonate = 140,
    ClientGMPacketID_Imitate = 141,
    ClientGMPacketID_RecordAdd = 142,
    ClientGMPacketID_RecordRemove = 143,
    ClientGMPacketID_RecordAddObs = 144,
    ClientGMPacketID_RecordListRequest = 145,
    ClientGMPacketID_RecordDetailsRequest = 146,
    ClientGMPacketID_AlterGuildName = 147,
    ClientGMPacketID_HigherAdminsMessage = 148,
    ClientGMPacketID_PACKET_COUNT = 149
};

class ClientGMPacket : public Packet {
public:
    explicit ClientGMPacket(int id) : Packet(id) { }
};

ClientGMPacket* ClientGMPacketFactory(clsByteQueue* buffer);

void ClientGMPacketDecodeAndDispatch(clsByteQueue* buffer, PacketHandler* handler);


class GMMessage : public ClientGMPacket {
public:
    GMMessage();
    GMMessage(clsByteQueue* buffer);
    GMMessage(const std::string& Chat);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Chat; 
};

inline GMMessage BuildGMMessage(const std::string& Chat) {
    return GMMessage(Chat);
}

class ShowName : public ClientGMPacket {
public:
    ShowName();
    ShowName(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ShowName BuildShowName() {
    return ShowName();
}

class OnlineRoyalArmy : public ClientGMPacket {
public:
    OnlineRoyalArmy();
    OnlineRoyalArmy(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline OnlineRoyalArmy BuildOnlineRoyalArmy() {
    return OnlineRoyalArmy();
}

class OnlineChaosLegion : public ClientGMPacket {
public:
    OnlineChaosLegion();
    OnlineChaosLegion(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline OnlineChaosLegion BuildOnlineChaosLegion() {
    return OnlineChaosLegion();
}

class GoNearby : public ClientGMPacket {
public:
    GoNearby();
    GoNearby(clsByteQueue* buffer);
    GoNearby(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline GoNearby BuildGoNearby(const std::string& UserName) {
    return GoNearby(UserName);
}

class Comment : public ClientGMPacket {
public:
    Comment();
    Comment(clsByteQueue* buffer);
    Comment(const std::string& Data);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Data; 
};

inline Comment BuildComment(const std::string& Data) {
    return Comment(Data);
}

class ServerTime : public ClientGMPacket {
public:
    ServerTime();
    ServerTime(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ServerTime BuildServerTime() {
    return ServerTime();
}

class Where : public ClientGMPacket {
public:
    Where();
    Where(clsByteQueue* buffer);
    Where(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline Where BuildWhere(const std::string& UserName) {
    return Where(UserName);
}

class CreaturesInMap : public ClientGMPacket {
public:
    CreaturesInMap();
    CreaturesInMap(clsByteQueue* buffer);
    CreaturesInMap(std::int16_t Map);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t Map; 
};

inline CreaturesInMap BuildCreaturesInMap(std::int16_t Map) {
    return CreaturesInMap(Map);
}

class WarpMeToTarget : public ClientGMPacket {
public:
    WarpMeToTarget();
    WarpMeToTarget(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline WarpMeToTarget BuildWarpMeToTarget() {
    return WarpMeToTarget();
}

class WarpChar : public ClientGMPacket {
public:
    WarpChar();
    WarpChar(clsByteQueue* buffer);
    WarpChar(const std::string& UserName, std::int16_t Map, std::uint8_t X, std::uint8_t Y);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::int16_t Map; 
    std::uint8_t X; 
    std::uint8_t Y; 
};

inline WarpChar BuildWarpChar(const std::string& UserName, std::int16_t Map, std::uint8_t X, std::uint8_t Y) {
    return WarpChar(UserName, Map, X, Y);
}

class Silence : public ClientGMPacket {
public:
    Silence();
    Silence(clsByteQueue* buffer);
    Silence(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline Silence BuildSilence(const std::string& UserName) {
    return Silence(UserName);
}

class SOSShowList : public ClientGMPacket {
public:
    SOSShowList();
    SOSShowList(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline SOSShowList BuildSOSShowList() {
    return SOSShowList();
}

class SOSRemove : public ClientGMPacket {
public:
    SOSRemove();
    SOSRemove(clsByteQueue* buffer);
    SOSRemove(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline SOSRemove BuildSOSRemove(const std::string& UserName) {
    return SOSRemove(UserName);
}

class GoToChar : public ClientGMPacket {
public:
    GoToChar();
    GoToChar(clsByteQueue* buffer);
    GoToChar(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline GoToChar BuildGoToChar(const std::string& UserName) {
    return GoToChar(UserName);
}

class Invisible : public ClientGMPacket {
public:
    Invisible();
    Invisible(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Invisible BuildInvisible() {
    return Invisible();
}

class GMPanel : public ClientGMPacket {
public:
    GMPanel();
    GMPanel(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline GMPanel BuildGMPanel() {
    return GMPanel();
}

class RequestUserList : public ClientGMPacket {
public:
    RequestUserList();
    RequestUserList(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RequestUserList BuildRequestUserList() {
    return RequestUserList();
}

class Working : public ClientGMPacket {
public:
    Working();
    Working(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Working BuildWorking() {
    return Working();
}

class Hiding : public ClientGMPacket {
public:
    Hiding();
    Hiding(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Hiding BuildHiding() {
    return Hiding();
}

class Jail : public ClientGMPacket {
public:
    Jail();
    Jail(clsByteQueue* buffer);
    Jail(const std::string& UserName, const std::string& Reason, std::uint8_t JailTime);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::string Reason; 
    std::uint8_t JailTime; 
};

inline Jail BuildJail(const std::string& UserName, const std::string& Reason, std::uint8_t JailTime) {
    return Jail(UserName, Reason, JailTime);
}

class KillNPC : public ClientGMPacket {
public:
    KillNPC();
    KillNPC(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline KillNPC BuildKillNPC() {
    return KillNPC();
}

class WarnUser : public ClientGMPacket {
public:
    WarnUser();
    WarnUser(clsByteQueue* buffer);
    WarnUser(const std::string& UserName, const std::string& Reason);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::string Reason; 
};

inline WarnUser BuildWarnUser(const std::string& UserName, const std::string& Reason) {
    return WarnUser(UserName, Reason);
}

class EditChar : public ClientGMPacket {
public:
    EditChar();
    EditChar(clsByteQueue* buffer);
    EditChar(const std::string& UserName, std::uint8_t Opcion, const std::string& Arg1, const std::string& Arg2);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::uint8_t Opcion; 
    std::string Arg1; 
    std::string Arg2; 
};

inline EditChar BuildEditChar(const std::string& UserName, std::uint8_t Opcion, const std::string& Arg1, const std::string& Arg2) {
    return EditChar(UserName, Opcion, Arg1, Arg2);
}

class RequestCharInfo : public ClientGMPacket {
public:
    RequestCharInfo();
    RequestCharInfo(clsByteQueue* buffer);
    RequestCharInfo(const std::string& TargetName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string TargetName; 
};

inline RequestCharInfo BuildRequestCharInfo(const std::string& TargetName) {
    return RequestCharInfo(TargetName);
}

class RequestCharStats : public ClientGMPacket {
public:
    RequestCharStats();
    RequestCharStats(clsByteQueue* buffer);
    RequestCharStats(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline RequestCharStats BuildRequestCharStats(const std::string& UserName) {
    return RequestCharStats(UserName);
}

class RequestCharGold : public ClientGMPacket {
public:
    RequestCharGold();
    RequestCharGold(clsByteQueue* buffer);
    RequestCharGold(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline RequestCharGold BuildRequestCharGold(const std::string& UserName) {
    return RequestCharGold(UserName);
}

class RequestCharInventory : public ClientGMPacket {
public:
    RequestCharInventory();
    RequestCharInventory(clsByteQueue* buffer);
    RequestCharInventory(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline RequestCharInventory BuildRequestCharInventory(const std::string& UserName) {
    return RequestCharInventory(UserName);
}

class RequestCharBank : public ClientGMPacket {
public:
    RequestCharBank();
    RequestCharBank(clsByteQueue* buffer);
    RequestCharBank(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline RequestCharBank BuildRequestCharBank(const std::string& UserName) {
    return RequestCharBank(UserName);
}

class RequestCharSkills : public ClientGMPacket {
public:
    RequestCharSkills();
    RequestCharSkills(clsByteQueue* buffer);
    RequestCharSkills(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline RequestCharSkills BuildRequestCharSkills(const std::string& UserName) {
    return RequestCharSkills(UserName);
}

class ReviveChar : public ClientGMPacket {
public:
    ReviveChar();
    ReviveChar(clsByteQueue* buffer);
    ReviveChar(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline ReviveChar BuildReviveChar(const std::string& UserName) {
    return ReviveChar(UserName);
}

class OnlineGM : public ClientGMPacket {
public:
    OnlineGM();
    OnlineGM(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline OnlineGM BuildOnlineGM() {
    return OnlineGM();
}

class OnlineMap : public ClientGMPacket {
public:
    OnlineMap();
    OnlineMap(clsByteQueue* buffer);
    OnlineMap(std::int16_t Map);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t Map; 
};

inline OnlineMap BuildOnlineMap(std::int16_t Map) {
    return OnlineMap(Map);
}

class Forgive : public ClientGMPacket {
public:
    Forgive();
    Forgive(clsByteQueue* buffer);
    Forgive(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline Forgive BuildForgive(const std::string& UserName) {
    return Forgive(UserName);
}

class Kick : public ClientGMPacket {
public:
    Kick();
    Kick(clsByteQueue* buffer);
    Kick(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline Kick BuildKick(const std::string& UserName) {
    return Kick(UserName);
}

class Execute : public ClientGMPacket {
public:
    Execute();
    Execute(clsByteQueue* buffer);
    Execute(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline Execute BuildExecute(const std::string& UserName) {
    return Execute(UserName);
}

class BanChar : public ClientGMPacket {
public:
    BanChar();
    BanChar(clsByteQueue* buffer);
    BanChar(const std::string& UserName, const std::string& Reason);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::string Reason; 
};

inline BanChar BuildBanChar(const std::string& UserName, const std::string& Reason) {
    return BanChar(UserName, Reason);
}

class UnbanChar : public ClientGMPacket {
public:
    UnbanChar();
    UnbanChar(clsByteQueue* buffer);
    UnbanChar(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline UnbanChar BuildUnbanChar(const std::string& UserName) {
    return UnbanChar(UserName);
}

class NPCFollow : public ClientGMPacket {
public:
    NPCFollow();
    NPCFollow(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline NPCFollow BuildNPCFollow() {
    return NPCFollow();
}

class SummonChar : public ClientGMPacket {
public:
    SummonChar();
    SummonChar(clsByteQueue* buffer);
    SummonChar(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline SummonChar BuildSummonChar(const std::string& UserName) {
    return SummonChar(UserName);
}

class SpawnListRequest : public ClientGMPacket {
public:
    SpawnListRequest();
    SpawnListRequest(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline SpawnListRequest BuildSpawnListRequest() {
    return SpawnListRequest();
}

class SpawnCreature : public ClientGMPacket {
public:
    SpawnCreature();
    SpawnCreature(clsByteQueue* buffer);
    SpawnCreature(std::int16_t NPC);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t NPC; 
};

inline SpawnCreature BuildSpawnCreature(std::int16_t NPC) {
    return SpawnCreature(NPC);
}

class ResetNPCInventory : public ClientGMPacket {
public:
    ResetNPCInventory();
    ResetNPCInventory(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ResetNPCInventory BuildResetNPCInventory() {
    return ResetNPCInventory();
}

class CleanWorld : public ClientGMPacket {
public:
    CleanWorld();
    CleanWorld(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline CleanWorld BuildCleanWorld() {
    return CleanWorld();
}

class ServerMessage : public ClientGMPacket {
public:
    ServerMessage();
    ServerMessage(clsByteQueue* buffer);
    ServerMessage(const std::string& Message);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Message; 
};

inline ServerMessage BuildServerMessage(const std::string& Message) {
    return ServerMessage(Message);
}

class NickToIP : public ClientGMPacket {
public:
    NickToIP();
    NickToIP(clsByteQueue* buffer);
    NickToIP(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline NickToIP BuildNickToIP(const std::string& UserName) {
    return NickToIP(UserName);
}

class IPToNick : public ClientGMPacket {
public:
    IPToNick();
    IPToNick(clsByteQueue* buffer);
    IPToNick(std::uint8_t A, std::uint8_t B, std::uint8_t C, std::uint8_t D);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t A; 
    std::uint8_t B; 
    std::uint8_t C; 
    std::uint8_t D; 
};

inline IPToNick BuildIPToNick(std::uint8_t A, std::uint8_t B, std::uint8_t C, std::uint8_t D) {
    return IPToNick(A, B, C, D);
}

class GuildOnlineMembers : public ClientGMPacket {
public:
    GuildOnlineMembers();
    GuildOnlineMembers(clsByteQueue* buffer);
    GuildOnlineMembers(const std::string& GuildName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string GuildName; 
};

inline GuildOnlineMembers BuildGuildOnlineMembers(const std::string& GuildName) {
    return GuildOnlineMembers(GuildName);
}

class TeleportCreate : public ClientGMPacket {
public:
    TeleportCreate();
    TeleportCreate(clsByteQueue* buffer);
    TeleportCreate(std::int16_t Map, std::uint8_t X, std::uint8_t Y, std::uint8_t Radio);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t Map; 
    std::uint8_t X; 
    std::uint8_t Y; 
    std::uint8_t Radio; 
};

inline TeleportCreate BuildTeleportCreate(std::int16_t Map, std::uint8_t X, std::uint8_t Y, std::uint8_t Radio) {
    return TeleportCreate(Map, X, Y, Radio);
}

class TeleportDestroy : public ClientGMPacket {
public:
    TeleportDestroy();
    TeleportDestroy(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline TeleportDestroy BuildTeleportDestroy() {
    return TeleportDestroy();
}

class RainToggle : public ClientGMPacket {
public:
    RainToggle();
    RainToggle(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RainToggle BuildRainToggle() {
    return RainToggle();
}

class SetCharDescription : public ClientGMPacket {
public:
    SetCharDescription();
    SetCharDescription(clsByteQueue* buffer);
    SetCharDescription(const std::string& Description);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Description; 
};

inline SetCharDescription BuildSetCharDescription(const std::string& Description) {
    return SetCharDescription(Description);
}

class ForceMIDIToMap : public ClientGMPacket {
public:
    ForceMIDIToMap();
    ForceMIDIToMap(clsByteQueue* buffer);
    ForceMIDIToMap(std::uint8_t MidiID, std::int16_t Map);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t MidiID; 
    std::int16_t Map; 
};

inline ForceMIDIToMap BuildForceMIDIToMap(std::uint8_t MidiID, std::int16_t Map) {
    return ForceMIDIToMap(MidiID, Map);
}

class ForceWAVEToMap : public ClientGMPacket {
public:
    ForceWAVEToMap();
    ForceWAVEToMap(clsByteQueue* buffer);
    ForceWAVEToMap(std::uint8_t Wave, std::int16_t Map, std::uint8_t X, std::uint8_t Y);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Wave; 
    std::int16_t Map; 
    std::uint8_t X; 
    std::uint8_t Y; 
};

inline ForceWAVEToMap BuildForceWAVEToMap(std::uint8_t Wave, std::int16_t Map, std::uint8_t X, std::uint8_t Y) {
    return ForceWAVEToMap(Wave, Map, X, Y);
}

class RoyalArmyMessage : public ClientGMPacket {
public:
    RoyalArmyMessage();
    RoyalArmyMessage(clsByteQueue* buffer);
    RoyalArmyMessage(const std::string& Message);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Message; 
};

inline RoyalArmyMessage BuildRoyalArmyMessage(const std::string& Message) {
    return RoyalArmyMessage(Message);
}

class ChaosLegionMessage : public ClientGMPacket {
public:
    ChaosLegionMessage();
    ChaosLegionMessage(clsByteQueue* buffer);
    ChaosLegionMessage(const std::string& Message);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Message; 
};

inline ChaosLegionMessage BuildChaosLegionMessage(const std::string& Message) {
    return ChaosLegionMessage(Message);
}

class CitizenMessage : public ClientGMPacket {
public:
    CitizenMessage();
    CitizenMessage(clsByteQueue* buffer);
    CitizenMessage(const std::string& Message);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Message; 
};

inline CitizenMessage BuildCitizenMessage(const std::string& Message) {
    return CitizenMessage(Message);
}

class CriminalMessage : public ClientGMPacket {
public:
    CriminalMessage();
    CriminalMessage(clsByteQueue* buffer);
    CriminalMessage(const std::string& Message);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Message; 
};

inline CriminalMessage BuildCriminalMessage(const std::string& Message) {
    return CriminalMessage(Message);
}

class TalkAsNPC : public ClientGMPacket {
public:
    TalkAsNPC();
    TalkAsNPC(clsByteQueue* buffer);
    TalkAsNPC(const std::string& Message);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Message; 
};

inline TalkAsNPC BuildTalkAsNPC(const std::string& Message) {
    return TalkAsNPC(Message);
}

class DestroyAllItemsInArea : public ClientGMPacket {
public:
    DestroyAllItemsInArea();
    DestroyAllItemsInArea(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline DestroyAllItemsInArea BuildDestroyAllItemsInArea() {
    return DestroyAllItemsInArea();
}

class AcceptRoyalCouncilMember : public ClientGMPacket {
public:
    AcceptRoyalCouncilMember();
    AcceptRoyalCouncilMember(clsByteQueue* buffer);
    AcceptRoyalCouncilMember(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline AcceptRoyalCouncilMember BuildAcceptRoyalCouncilMember(const std::string& UserName) {
    return AcceptRoyalCouncilMember(UserName);
}

class AcceptChaosCouncilMember : public ClientGMPacket {
public:
    AcceptChaosCouncilMember();
    AcceptChaosCouncilMember(clsByteQueue* buffer);
    AcceptChaosCouncilMember(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline AcceptChaosCouncilMember BuildAcceptChaosCouncilMember(const std::string& UserName) {
    return AcceptChaosCouncilMember(UserName);
}

class ItemsInTheFloor : public ClientGMPacket {
public:
    ItemsInTheFloor();
    ItemsInTheFloor(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ItemsInTheFloor BuildItemsInTheFloor() {
    return ItemsInTheFloor();
}

class MakeDumb : public ClientGMPacket {
public:
    MakeDumb();
    MakeDumb(clsByteQueue* buffer);
    MakeDumb(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline MakeDumb BuildMakeDumb(const std::string& UserName) {
    return MakeDumb(UserName);
}

class MakeDumbNoMore : public ClientGMPacket {
public:
    MakeDumbNoMore();
    MakeDumbNoMore(clsByteQueue* buffer);
    MakeDumbNoMore(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline MakeDumbNoMore BuildMakeDumbNoMore(const std::string& UserName) {
    return MakeDumbNoMore(UserName);
}

class DumpIPTables : public ClientGMPacket {
public:
    DumpIPTables();
    DumpIPTables(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline DumpIPTables BuildDumpIPTables() {
    return DumpIPTables();
}

class CouncilKick : public ClientGMPacket {
public:
    CouncilKick();
    CouncilKick(clsByteQueue* buffer);
    CouncilKick(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline CouncilKick BuildCouncilKick(const std::string& UserName) {
    return CouncilKick(UserName);
}

class SetTrigger : public ClientGMPacket {
public:
    SetTrigger();
    SetTrigger(clsByteQueue* buffer);
    SetTrigger(std::uint8_t Trigger);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Trigger; 
};

inline SetTrigger BuildSetTrigger(std::uint8_t Trigger) {
    return SetTrigger(Trigger);
}

class AskTrigger : public ClientGMPacket {
public:
    AskTrigger();
    AskTrigger(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline AskTrigger BuildAskTrigger() {
    return AskTrigger();
}

class BannedIPList : public ClientGMPacket {
public:
    BannedIPList();
    BannedIPList(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline BannedIPList BuildBannedIPList() {
    return BannedIPList();
}

class BannedIPReload : public ClientGMPacket {
public:
    BannedIPReload();
    BannedIPReload(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline BannedIPReload BuildBannedIPReload() {
    return BannedIPReload();
}

class GuildMemberList : public ClientGMPacket {
public:
    GuildMemberList();
    GuildMemberList(clsByteQueue* buffer);
    GuildMemberList(const std::string& GuildName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string GuildName; 
};

inline GuildMemberList BuildGuildMemberList(const std::string& GuildName) {
    return GuildMemberList(GuildName);
}

class GuildBan : public ClientGMPacket {
public:
    GuildBan();
    GuildBan(clsByteQueue* buffer);
    GuildBan(const std::string& GuildName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string GuildName; 
};

inline GuildBan BuildGuildBan(const std::string& GuildName) {
    return GuildBan(GuildName);
}

class BanIP : public ClientGMPacket {
public:
    BanIP();
    BanIP(clsByteQueue* buffer);
    BanIP(const std::string& IP, const std::string& Reason);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string IP; 
    std::string Reason; 
};

inline BanIP BuildBanIP(const std::string& IP, const std::string& Reason) {
    return BanIP(IP, Reason);
}

class UnbanIP : public ClientGMPacket {
public:
    UnbanIP();
    UnbanIP(clsByteQueue* buffer);
    UnbanIP(const std::string& IP);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string IP; 
};

inline UnbanIP BuildUnbanIP(const std::string& IP) {
    return UnbanIP(IP);
}

class CreateItem : public ClientGMPacket {
public:
    CreateItem();
    CreateItem(clsByteQueue* buffer);
    CreateItem(std::int16_t Item);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t Item; 
};

inline CreateItem BuildCreateItem(std::int16_t Item) {
    return CreateItem(Item);
}

class DestroyItems : public ClientGMPacket {
public:
    DestroyItems();
    DestroyItems(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline DestroyItems BuildDestroyItems() {
    return DestroyItems();
}

class ChaosLegionKick : public ClientGMPacket {
public:
    ChaosLegionKick();
    ChaosLegionKick(clsByteQueue* buffer);
    ChaosLegionKick(const std::string& UserName, const std::string& Reason);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::string Reason; 
};

inline ChaosLegionKick BuildChaosLegionKick(const std::string& UserName, const std::string& Reason) {
    return ChaosLegionKick(UserName, Reason);
}

class RoyalArmyKick : public ClientGMPacket {
public:
    RoyalArmyKick();
    RoyalArmyKick(clsByteQueue* buffer);
    RoyalArmyKick(const std::string& UserName, const std::string& Reason);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::string Reason; 
};

inline RoyalArmyKick BuildRoyalArmyKick(const std::string& UserName, const std::string& Reason) {
    return RoyalArmyKick(UserName, Reason);
}

class ForceMIDIAll : public ClientGMPacket {
public:
    ForceMIDIAll();
    ForceMIDIAll(clsByteQueue* buffer);
    ForceMIDIAll(std::uint8_t MidiID);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t MidiID; 
};

inline ForceMIDIAll BuildForceMIDIAll(std::uint8_t MidiID) {
    return ForceMIDIAll(MidiID);
}

class ForceWAVEAll : public ClientGMPacket {
public:
    ForceWAVEAll();
    ForceWAVEAll(clsByteQueue* buffer);
    ForceWAVEAll(std::uint8_t WaveID);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t WaveID; 
};

inline ForceWAVEAll BuildForceWAVEAll(std::uint8_t WaveID) {
    return ForceWAVEAll(WaveID);
}

class RemovePunishment : public ClientGMPacket {
public:
    RemovePunishment();
    RemovePunishment(clsByteQueue* buffer);
    RemovePunishment(const std::string& UserName, std::uint8_t Punishment, const std::string& NewText);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::uint8_t Punishment; 
    std::string NewText; 
};

inline RemovePunishment BuildRemovePunishment(const std::string& UserName, std::uint8_t Punishment, const std::string& NewText) {
    return RemovePunishment(UserName, Punishment, NewText);
}

class TileBlockedToggle : public ClientGMPacket {
public:
    TileBlockedToggle();
    TileBlockedToggle(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline TileBlockedToggle BuildTileBlockedToggle() {
    return TileBlockedToggle();
}

class KillNPCNoRespawn : public ClientGMPacket {
public:
    KillNPCNoRespawn();
    KillNPCNoRespawn(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline KillNPCNoRespawn BuildKillNPCNoRespawn() {
    return KillNPCNoRespawn();
}

class KillAllNearbyNPCs : public ClientGMPacket {
public:
    KillAllNearbyNPCs();
    KillAllNearbyNPCs(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline KillAllNearbyNPCs BuildKillAllNearbyNPCs() {
    return KillAllNearbyNPCs();
}

class LastIP : public ClientGMPacket {
public:
    LastIP();
    LastIP(clsByteQueue* buffer);
    LastIP(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline LastIP BuildLastIP(const std::string& UserName) {
    return LastIP(UserName);
}

class ChangeMOTD : public ClientGMPacket {
public:
    ChangeMOTD();
    ChangeMOTD(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ChangeMOTD BuildChangeMOTD() {
    return ChangeMOTD();
}

class SetMOTD : public ClientGMPacket {
public:
    SetMOTD();
    SetMOTD(clsByteQueue* buffer);
    SetMOTD(const std::string& Motd);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Motd; 
};

inline SetMOTD BuildSetMOTD(const std::string& Motd) {
    return SetMOTD(Motd);
}

class SystemMessage : public ClientGMPacket {
public:
    SystemMessage();
    SystemMessage(clsByteQueue* buffer);
    SystemMessage(const std::string& Message);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Message; 
};

inline SystemMessage BuildSystemMessage(const std::string& Message) {
    return SystemMessage(Message);
}

class CreateNPC : public ClientGMPacket {
public:
    CreateNPC();
    CreateNPC(clsByteQueue* buffer);
    CreateNPC(std::int16_t NpcIndex);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t NpcIndex; 
};

inline CreateNPC BuildCreateNPC(std::int16_t NpcIndex) {
    return CreateNPC(NpcIndex);
}

class CreateNPCWithRespawn : public ClientGMPacket {
public:
    CreateNPCWithRespawn();
    CreateNPCWithRespawn(clsByteQueue* buffer);
    CreateNPCWithRespawn(std::int16_t NpcIndex);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t NpcIndex; 
};

inline CreateNPCWithRespawn BuildCreateNPCWithRespawn(std::int16_t NpcIndex) {
    return CreateNPCWithRespawn(NpcIndex);
}

class ImperialArmour : public ClientGMPacket {
public:
    ImperialArmour();
    ImperialArmour(clsByteQueue* buffer);
    ImperialArmour(std::uint8_t Index, std::int16_t ObjIndex);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Index; 
    std::int16_t ObjIndex; 
};

inline ImperialArmour BuildImperialArmour(std::uint8_t Index, std::int16_t ObjIndex) {
    return ImperialArmour(Index, ObjIndex);
}

class ChaosArmour : public ClientGMPacket {
public:
    ChaosArmour();
    ChaosArmour(clsByteQueue* buffer);
    ChaosArmour(std::uint8_t Index, std::int16_t ObjIndex);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Index; 
    std::int16_t ObjIndex; 
};

inline ChaosArmour BuildChaosArmour(std::uint8_t Index, std::int16_t ObjIndex) {
    return ChaosArmour(Index, ObjIndex);
}

class NavigateToggle : public ClientGMPacket {
public:
    NavigateToggle();
    NavigateToggle(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline NavigateToggle BuildNavigateToggle() {
    return NavigateToggle();
}

class ServerOpenToUsersToggle : public ClientGMPacket {
public:
    ServerOpenToUsersToggle();
    ServerOpenToUsersToggle(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ServerOpenToUsersToggle BuildServerOpenToUsersToggle() {
    return ServerOpenToUsersToggle();
}

class TurnOffServer : public ClientGMPacket {
public:
    TurnOffServer();
    TurnOffServer(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline TurnOffServer BuildTurnOffServer() {
    return TurnOffServer();
}

class TurnCriminal : public ClientGMPacket {
public:
    TurnCriminal();
    TurnCriminal(clsByteQueue* buffer);
    TurnCriminal(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline TurnCriminal BuildTurnCriminal(const std::string& UserName) {
    return TurnCriminal(UserName);
}

class ResetFactions : public ClientGMPacket {
public:
    ResetFactions();
    ResetFactions(clsByteQueue* buffer);
    ResetFactions(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline ResetFactions BuildResetFactions(const std::string& UserName) {
    return ResetFactions(UserName);
}

class RemoveCharFromGuild : public ClientGMPacket {
public:
    RemoveCharFromGuild();
    RemoveCharFromGuild(clsByteQueue* buffer);
    RemoveCharFromGuild(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline RemoveCharFromGuild BuildRemoveCharFromGuild(const std::string& UserName) {
    return RemoveCharFromGuild(UserName);
}

class RequestCharMail : public ClientGMPacket {
public:
    RequestCharMail();
    RequestCharMail(clsByteQueue* buffer);
    RequestCharMail(const std::string& UserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline RequestCharMail BuildRequestCharMail(const std::string& UserName) {
    return RequestCharMail(UserName);
}

class AlterPassword : public ClientGMPacket {
public:
    AlterPassword();
    AlterPassword(clsByteQueue* buffer);
    AlterPassword(const std::string& UserName, const std::string& CopyFrom);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::string CopyFrom; 
};

inline AlterPassword BuildAlterPassword(const std::string& UserName, const std::string& CopyFrom) {
    return AlterPassword(UserName, CopyFrom);
}

class AlterMail : public ClientGMPacket {
public:
    AlterMail();
    AlterMail(clsByteQueue* buffer);
    AlterMail(const std::string& UserName, const std::string& NewMail);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::string NewMail; 
};

inline AlterMail BuildAlterMail(const std::string& UserName, const std::string& NewMail) {
    return AlterMail(UserName, NewMail);
}

class AlterName : public ClientGMPacket {
public:
    AlterName();
    AlterName(clsByteQueue* buffer);
    AlterName(const std::string& UserName, const std::string& NewName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::string NewName; 
};

inline AlterName BuildAlterName(const std::string& UserName, const std::string& NewName) {
    return AlterName(UserName, NewName);
}

class ToggleCentinelActivated : public ClientGMPacket {
public:
    ToggleCentinelActivated();
    ToggleCentinelActivated(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ToggleCentinelActivated BuildToggleCentinelActivated() {
    return ToggleCentinelActivated();
}

class DoBackUp : public ClientGMPacket {
public:
    DoBackUp();
    DoBackUp(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline DoBackUp BuildDoBackUp() {
    return DoBackUp();
}

class ShowGuildMessages : public ClientGMPacket {
public:
    ShowGuildMessages();
    ShowGuildMessages(clsByteQueue* buffer);
    ShowGuildMessages(const std::string& GuildName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string GuildName; 
};

inline ShowGuildMessages BuildShowGuildMessages(const std::string& GuildName) {
    return ShowGuildMessages(GuildName);
}

class SaveMap : public ClientGMPacket {
public:
    SaveMap();
    SaveMap(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline SaveMap BuildSaveMap() {
    return SaveMap();
}

class ChangeMapInfoPK : public ClientGMPacket {
public:
    ChangeMapInfoPK();
    ChangeMapInfoPK(clsByteQueue* buffer);
    ChangeMapInfoPK(bool Pk);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    bool Pk; 
};

inline ChangeMapInfoPK BuildChangeMapInfoPK(bool Pk) {
    return ChangeMapInfoPK(Pk);
}

class ChangeMapInfoBackup : public ClientGMPacket {
public:
    ChangeMapInfoBackup();
    ChangeMapInfoBackup(clsByteQueue* buffer);
    ChangeMapInfoBackup(bool Backup);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    bool Backup; 
};

inline ChangeMapInfoBackup BuildChangeMapInfoBackup(bool Backup) {
    return ChangeMapInfoBackup(Backup);
}

class ChangeMapInfoRestricted : public ClientGMPacket {
public:
    ChangeMapInfoRestricted();
    ChangeMapInfoRestricted(clsByteQueue* buffer);
    ChangeMapInfoRestricted(const std::string& RestrictedTo);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string RestrictedTo; 
};

inline ChangeMapInfoRestricted BuildChangeMapInfoRestricted(const std::string& RestrictedTo) {
    return ChangeMapInfoRestricted(RestrictedTo);
}

class ChangeMapInfoNoMagic : public ClientGMPacket {
public:
    ChangeMapInfoNoMagic();
    ChangeMapInfoNoMagic(clsByteQueue* buffer);
    ChangeMapInfoNoMagic(bool NoMagic);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    bool NoMagic; 
};

inline ChangeMapInfoNoMagic BuildChangeMapInfoNoMagic(bool NoMagic) {
    return ChangeMapInfoNoMagic(NoMagic);
}

class ChangeMapInfoNoInvi : public ClientGMPacket {
public:
    ChangeMapInfoNoInvi();
    ChangeMapInfoNoInvi(clsByteQueue* buffer);
    ChangeMapInfoNoInvi(bool NoInvi);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    bool NoInvi; 
};

inline ChangeMapInfoNoInvi BuildChangeMapInfoNoInvi(bool NoInvi) {
    return ChangeMapInfoNoInvi(NoInvi);
}

class ChangeMapInfoNoResu : public ClientGMPacket {
public:
    ChangeMapInfoNoResu();
    ChangeMapInfoNoResu(clsByteQueue* buffer);
    ChangeMapInfoNoResu(bool NoResu);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    bool NoResu; 
};

inline ChangeMapInfoNoResu BuildChangeMapInfoNoResu(bool NoResu) {
    return ChangeMapInfoNoResu(NoResu);
}

class ChangeMapInfoLand : public ClientGMPacket {
public:
    ChangeMapInfoLand();
    ChangeMapInfoLand(clsByteQueue* buffer);
    ChangeMapInfoLand(const std::string& Data);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Data; 
};

inline ChangeMapInfoLand BuildChangeMapInfoLand(const std::string& Data) {
    return ChangeMapInfoLand(Data);
}

class ChangeMapInfoZone : public ClientGMPacket {
public:
    ChangeMapInfoZone();
    ChangeMapInfoZone(clsByteQueue* buffer);
    ChangeMapInfoZone(const std::string& Data);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Data; 
};

inline ChangeMapInfoZone BuildChangeMapInfoZone(const std::string& Data) {
    return ChangeMapInfoZone(Data);
}

class ChangeMapInfoStealNpc : public ClientGMPacket {
public:
    ChangeMapInfoStealNpc();
    ChangeMapInfoStealNpc(clsByteQueue* buffer);
    ChangeMapInfoStealNpc(bool RoboNpc);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    bool RoboNpc; 
};

inline ChangeMapInfoStealNpc BuildChangeMapInfoStealNpc(bool RoboNpc) {
    return ChangeMapInfoStealNpc(RoboNpc);
}

class ChangeMapInfoNoOcultar : public ClientGMPacket {
public:
    ChangeMapInfoNoOcultar();
    ChangeMapInfoNoOcultar(clsByteQueue* buffer);
    ChangeMapInfoNoOcultar(bool NoOcultar);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    bool NoOcultar; 
};

inline ChangeMapInfoNoOcultar BuildChangeMapInfoNoOcultar(bool NoOcultar) {
    return ChangeMapInfoNoOcultar(NoOcultar);
}

class ChangeMapInfoNoInvocar : public ClientGMPacket {
public:
    ChangeMapInfoNoInvocar();
    ChangeMapInfoNoInvocar(clsByteQueue* buffer);
    ChangeMapInfoNoInvocar(bool NoInvocar);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    bool NoInvocar; 
};

inline ChangeMapInfoNoInvocar BuildChangeMapInfoNoInvocar(bool NoInvocar) {
    return ChangeMapInfoNoInvocar(NoInvocar);
}

class SaveChars : public ClientGMPacket {
public:
    SaveChars();
    SaveChars(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline SaveChars BuildSaveChars() {
    return SaveChars();
}

class CleanSOS : public ClientGMPacket {
public:
    CleanSOS();
    CleanSOS(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline CleanSOS BuildCleanSOS() {
    return CleanSOS();
}

class ShowServerForm : public ClientGMPacket {
public:
    ShowServerForm();
    ShowServerForm(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ShowServerForm BuildShowServerForm() {
    return ShowServerForm();
}

class Night : public ClientGMPacket {
public:
    Night();
    Night(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Night BuildNight() {
    return Night();
}

class KickAllChars : public ClientGMPacket {
public:
    KickAllChars();
    KickAllChars(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline KickAllChars BuildKickAllChars() {
    return KickAllChars();
}

class ReloadNPCs : public ClientGMPacket {
public:
    ReloadNPCs();
    ReloadNPCs(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ReloadNPCs BuildReloadNPCs() {
    return ReloadNPCs();
}

class ReloadServerIni : public ClientGMPacket {
public:
    ReloadServerIni();
    ReloadServerIni(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ReloadServerIni BuildReloadServerIni() {
    return ReloadServerIni();
}

class ReloadSpells : public ClientGMPacket {
public:
    ReloadSpells();
    ReloadSpells(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ReloadSpells BuildReloadSpells() {
    return ReloadSpells();
}

class ReloadObjects : public ClientGMPacket {
public:
    ReloadObjects();
    ReloadObjects(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ReloadObjects BuildReloadObjects() {
    return ReloadObjects();
}

class Restart : public ClientGMPacket {
public:
    Restart();
    Restart(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Restart BuildRestart() {
    return Restart();
}

class ResetAutoUpdate : public ClientGMPacket {
public:
    ResetAutoUpdate();
    ResetAutoUpdate(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ResetAutoUpdate BuildResetAutoUpdate() {
    return ResetAutoUpdate();
}

class ChatColor : public ClientGMPacket {
public:
    ChatColor();
    ChatColor(clsByteQueue* buffer);
    ChatColor(std::uint8_t R, std::uint8_t G, std::uint8_t B);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t R; 
    std::uint8_t G; 
    std::uint8_t B; 
};

inline ChatColor BuildChatColor(std::uint8_t R, std::uint8_t G, std::uint8_t B) {
    return ChatColor(R, G, B);
}

class Ignored : public ClientGMPacket {
public:
    Ignored();
    Ignored(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Ignored BuildIgnored() {
    return Ignored();
}

class CheckSlot : public ClientGMPacket {
public:
    CheckSlot();
    CheckSlot(clsByteQueue* buffer);
    CheckSlot(const std::string& UserName, std::uint8_t Slot);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::uint8_t Slot; 
};

inline CheckSlot BuildCheckSlot(const std::string& UserName, std::uint8_t Slot) {
    return CheckSlot(UserName, Slot);
}

class SetIniVar : public ClientGMPacket {
public:
    SetIniVar();
    SetIniVar(clsByteQueue* buffer);
    SetIniVar(const std::string& Seccion, const std::string& Clave, const std::string& Valor);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Seccion; 
    std::string Clave; 
    std::string Valor; 
};

inline SetIniVar BuildSetIniVar(const std::string& Seccion, const std::string& Clave, const std::string& Valor) {
    return SetIniVar(Seccion, Clave, Valor);
}

class CreatePretorianClan : public ClientGMPacket {
public:
    CreatePretorianClan();
    CreatePretorianClan(clsByteQueue* buffer);
    CreatePretorianClan(std::int16_t Map, std::uint8_t X, std::uint8_t Y);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t Map; 
    std::uint8_t X; 
    std::uint8_t Y; 
};

inline CreatePretorianClan BuildCreatePretorianClan(std::int16_t Map, std::uint8_t X, std::uint8_t Y) {
    return CreatePretorianClan(Map, X, Y);
}

class RemovePretorianClan : public ClientGMPacket {
public:
    RemovePretorianClan();
    RemovePretorianClan(clsByteQueue* buffer);
    RemovePretorianClan(std::int16_t Map);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t Map; 
};

inline RemovePretorianClan BuildRemovePretorianClan(std::int16_t Map) {
    return RemovePretorianClan(Map);
}

class EnableDenounces : public ClientGMPacket {
public:
    EnableDenounces();
    EnableDenounces(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline EnableDenounces BuildEnableDenounces() {
    return EnableDenounces();
}

class ShowDenouncesList : public ClientGMPacket {
public:
    ShowDenouncesList();
    ShowDenouncesList(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ShowDenouncesList BuildShowDenouncesList() {
    return ShowDenouncesList();
}

class MapMessage : public ClientGMPacket {
public:
    MapMessage();
    MapMessage(clsByteQueue* buffer);
    MapMessage(const std::string& Message);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Message; 
};

inline MapMessage BuildMapMessage(const std::string& Message) {
    return MapMessage(Message);
}

class SetDialog : public ClientGMPacket {
public:
    SetDialog();
    SetDialog(clsByteQueue* buffer);
    SetDialog(const std::string& Message);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Message; 
};

inline SetDialog BuildSetDialog(const std::string& Message) {
    return SetDialog(Message);
}

class Impersonate : public ClientGMPacket {
public:
    Impersonate();
    Impersonate(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Impersonate BuildImpersonate() {
    return Impersonate();
}

class Imitate : public ClientGMPacket {
public:
    Imitate();
    Imitate(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Imitate BuildImitate() {
    return Imitate();
}

class RecordAdd : public ClientGMPacket {
public:
    RecordAdd();
    RecordAdd(clsByteQueue* buffer);
    RecordAdd(const std::string& UserName, const std::string& Reason);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::string Reason; 
};

inline RecordAdd BuildRecordAdd(const std::string& UserName, const std::string& Reason) {
    return RecordAdd(UserName, Reason);
}

class RecordRemove : public ClientGMPacket {
public:
    RecordRemove();
    RecordRemove(clsByteQueue* buffer);
    RecordRemove(std::uint8_t Index);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Index; 
};

inline RecordRemove BuildRecordRemove(std::uint8_t Index) {
    return RecordRemove(Index);
}

class RecordAddObs : public ClientGMPacket {
public:
    RecordAddObs();
    RecordAddObs(clsByteQueue* buffer);
    RecordAddObs(std::uint8_t Index, const std::string& Obs);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Index; 
    std::string Obs; 
};

inline RecordAddObs BuildRecordAddObs(std::uint8_t Index, const std::string& Obs) {
    return RecordAddObs(Index, Obs);
}

class RecordListRequest : public ClientGMPacket {
public:
    RecordListRequest();
    RecordListRequest(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RecordListRequest BuildRecordListRequest() {
    return RecordListRequest();
}

class RecordDetailsRequest : public ClientGMPacket {
public:
    RecordDetailsRequest();
    RecordDetailsRequest(clsByteQueue* buffer);
    RecordDetailsRequest(std::uint8_t Index);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Index; 
};

inline RecordDetailsRequest BuildRecordDetailsRequest(std::uint8_t Index) {
    return RecordDetailsRequest(Index);
}

class AlterGuildName : public ClientGMPacket {
public:
    AlterGuildName();
    AlterGuildName(clsByteQueue* buffer);
    AlterGuildName(const std::string& OldGuildName, const std::string& NewGuildName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string OldGuildName; 
    std::string NewGuildName; 
};

inline AlterGuildName BuildAlterGuildName(const std::string& OldGuildName, const std::string& NewGuildName) {
    return AlterGuildName(OldGuildName, NewGuildName);
}

class HigherAdminsMessage : public ClientGMPacket {
public:
    HigherAdminsMessage();
    HigherAdminsMessage(clsByteQueue* buffer);
    HigherAdminsMessage(const std::string& Message);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Message; 
};

inline HigherAdminsMessage BuildHigherAdminsMessage(const std::string& Message) {
    return HigherAdminsMessage(Message);
}

class ClientGMPacketHandler {
public:
    virtual ~ClientGMPacketHandler();

    virtual void handleGMMessage(GMMessage* p);
    virtual void handleShowName(ShowName* p);
    virtual void handleOnlineRoyalArmy(OnlineRoyalArmy* p);
    virtual void handleOnlineChaosLegion(OnlineChaosLegion* p);
    virtual void handleGoNearby(GoNearby* p);
    virtual void handleComment(Comment* p);
    virtual void handleServerTime(ServerTime* p);
    virtual void handleWhere(Where* p);
    virtual void handleCreaturesInMap(CreaturesInMap* p);
    virtual void handleWarpMeToTarget(WarpMeToTarget* p);
    virtual void handleWarpChar(WarpChar* p);
    virtual void handleSilence(Silence* p);
    virtual void handleSOSShowList(SOSShowList* p);
    virtual void handleSOSRemove(SOSRemove* p);
    virtual void handleGoToChar(GoToChar* p);
    virtual void handleInvisible(Invisible* p);
    virtual void handleGMPanel(GMPanel* p);
    virtual void handleRequestUserList(RequestUserList* p);
    virtual void handleWorking(Working* p);
    virtual void handleHiding(Hiding* p);
    virtual void handleJail(Jail* p);
    virtual void handleKillNPC(KillNPC* p);
    virtual void handleWarnUser(WarnUser* p);
    virtual void handleEditChar(EditChar* p);
    virtual void handleRequestCharInfo(RequestCharInfo* p);
    virtual void handleRequestCharStats(RequestCharStats* p);
    virtual void handleRequestCharGold(RequestCharGold* p);
    virtual void handleRequestCharInventory(RequestCharInventory* p);
    virtual void handleRequestCharBank(RequestCharBank* p);
    virtual void handleRequestCharSkills(RequestCharSkills* p);
    virtual void handleReviveChar(ReviveChar* p);
    virtual void handleOnlineGM(OnlineGM* p);
    virtual void handleOnlineMap(OnlineMap* p);
    virtual void handleForgive(Forgive* p);
    virtual void handleKick(Kick* p);
    virtual void handleExecute(Execute* p);
    virtual void handleBanChar(BanChar* p);
    virtual void handleUnbanChar(UnbanChar* p);
    virtual void handleNPCFollow(NPCFollow* p);
    virtual void handleSummonChar(SummonChar* p);
    virtual void handleSpawnListRequest(SpawnListRequest* p);
    virtual void handleSpawnCreature(SpawnCreature* p);
    virtual void handleResetNPCInventory(ResetNPCInventory* p);
    virtual void handleCleanWorld(CleanWorld* p);
    virtual void handleServerMessage(ServerMessage* p);
    virtual void handleNickToIP(NickToIP* p);
    virtual void handleIPToNick(IPToNick* p);
    virtual void handleGuildOnlineMembers(GuildOnlineMembers* p);
    virtual void handleTeleportCreate(TeleportCreate* p);
    virtual void handleTeleportDestroy(TeleportDestroy* p);
    virtual void handleRainToggle(RainToggle* p);
    virtual void handleSetCharDescription(SetCharDescription* p);
    virtual void handleForceMIDIToMap(ForceMIDIToMap* p);
    virtual void handleForceWAVEToMap(ForceWAVEToMap* p);
    virtual void handleRoyalArmyMessage(RoyalArmyMessage* p);
    virtual void handleChaosLegionMessage(ChaosLegionMessage* p);
    virtual void handleCitizenMessage(CitizenMessage* p);
    virtual void handleCriminalMessage(CriminalMessage* p);
    virtual void handleTalkAsNPC(TalkAsNPC* p);
    virtual void handleDestroyAllItemsInArea(DestroyAllItemsInArea* p);
    virtual void handleAcceptRoyalCouncilMember(AcceptRoyalCouncilMember* p);
    virtual void handleAcceptChaosCouncilMember(AcceptChaosCouncilMember* p);
    virtual void handleItemsInTheFloor(ItemsInTheFloor* p);
    virtual void handleMakeDumb(MakeDumb* p);
    virtual void handleMakeDumbNoMore(MakeDumbNoMore* p);
    virtual void handleDumpIPTables(DumpIPTables* p);
    virtual void handleCouncilKick(CouncilKick* p);
    virtual void handleSetTrigger(SetTrigger* p);
    virtual void handleAskTrigger(AskTrigger* p);
    virtual void handleBannedIPList(BannedIPList* p);
    virtual void handleBannedIPReload(BannedIPReload* p);
    virtual void handleGuildMemberList(GuildMemberList* p);
    virtual void handleGuildBan(GuildBan* p);
    virtual void handleBanIP(BanIP* p);
    virtual void handleUnbanIP(UnbanIP* p);
    virtual void handleCreateItem(CreateItem* p);
    virtual void handleDestroyItems(DestroyItems* p);
    virtual void handleChaosLegionKick(ChaosLegionKick* p);
    virtual void handleRoyalArmyKick(RoyalArmyKick* p);
    virtual void handleForceMIDIAll(ForceMIDIAll* p);
    virtual void handleForceWAVEAll(ForceWAVEAll* p);
    virtual void handleRemovePunishment(RemovePunishment* p);
    virtual void handleTileBlockedToggle(TileBlockedToggle* p);
    virtual void handleKillNPCNoRespawn(KillNPCNoRespawn* p);
    virtual void handleKillAllNearbyNPCs(KillAllNearbyNPCs* p);
    virtual void handleLastIP(LastIP* p);
    virtual void handleChangeMOTD(ChangeMOTD* p);
    virtual void handleSetMOTD(SetMOTD* p);
    virtual void handleSystemMessage(SystemMessage* p);
    virtual void handleCreateNPC(CreateNPC* p);
    virtual void handleCreateNPCWithRespawn(CreateNPCWithRespawn* p);
    virtual void handleImperialArmour(ImperialArmour* p);
    virtual void handleChaosArmour(ChaosArmour* p);
    virtual void handleNavigateToggle(NavigateToggle* p);
    virtual void handleServerOpenToUsersToggle(ServerOpenToUsersToggle* p);
    virtual void handleTurnOffServer(TurnOffServer* p);
    virtual void handleTurnCriminal(TurnCriminal* p);
    virtual void handleResetFactions(ResetFactions* p);
    virtual void handleRemoveCharFromGuild(RemoveCharFromGuild* p);
    virtual void handleRequestCharMail(RequestCharMail* p);
    virtual void handleAlterPassword(AlterPassword* p);
    virtual void handleAlterMail(AlterMail* p);
    virtual void handleAlterName(AlterName* p);
    virtual void handleToggleCentinelActivated(ToggleCentinelActivated* p);
    virtual void handleDoBackUp(DoBackUp* p);
    virtual void handleShowGuildMessages(ShowGuildMessages* p);
    virtual void handleSaveMap(SaveMap* p);
    virtual void handleChangeMapInfoPK(ChangeMapInfoPK* p);
    virtual void handleChangeMapInfoBackup(ChangeMapInfoBackup* p);
    virtual void handleChangeMapInfoRestricted(ChangeMapInfoRestricted* p);
    virtual void handleChangeMapInfoNoMagic(ChangeMapInfoNoMagic* p);
    virtual void handleChangeMapInfoNoInvi(ChangeMapInfoNoInvi* p);
    virtual void handleChangeMapInfoNoResu(ChangeMapInfoNoResu* p);
    virtual void handleChangeMapInfoLand(ChangeMapInfoLand* p);
    virtual void handleChangeMapInfoZone(ChangeMapInfoZone* p);
    virtual void handleChangeMapInfoStealNpc(ChangeMapInfoStealNpc* p);
    virtual void handleChangeMapInfoNoOcultar(ChangeMapInfoNoOcultar* p);
    virtual void handleChangeMapInfoNoInvocar(ChangeMapInfoNoInvocar* p);
    virtual void handleSaveChars(SaveChars* p);
    virtual void handleCleanSOS(CleanSOS* p);
    virtual void handleShowServerForm(ShowServerForm* p);
    virtual void handleNight(Night* p);
    virtual void handleKickAllChars(KickAllChars* p);
    virtual void handleReloadNPCs(ReloadNPCs* p);
    virtual void handleReloadServerIni(ReloadServerIni* p);
    virtual void handleReloadSpells(ReloadSpells* p);
    virtual void handleReloadObjects(ReloadObjects* p);
    virtual void handleRestart(Restart* p);
    virtual void handleResetAutoUpdate(ResetAutoUpdate* p);
    virtual void handleChatColor(ChatColor* p);
    virtual void handleIgnored(Ignored* p);
    virtual void handleCheckSlot(CheckSlot* p);
    virtual void handleSetIniVar(SetIniVar* p);
    virtual void handleCreatePretorianClan(CreatePretorianClan* p);
    virtual void handleRemovePretorianClan(RemovePretorianClan* p);
    virtual void handleEnableDenounces(EnableDenounces* p);
    virtual void handleShowDenouncesList(ShowDenouncesList* p);
    virtual void handleMapMessage(MapMessage* p);
    virtual void handleSetDialog(SetDialog* p);
    virtual void handleImpersonate(Impersonate* p);
    virtual void handleImitate(Imitate* p);
    virtual void handleRecordAdd(RecordAdd* p);
    virtual void handleRecordRemove(RecordRemove* p);
    virtual void handleRecordAddObs(RecordAddObs* p);
    virtual void handleRecordListRequest(RecordListRequest* p);
    virtual void handleRecordDetailsRequest(RecordDetailsRequest* p);
    virtual void handleAlterGuildName(AlterGuildName* p);
    virtual void handleHigherAdminsMessage(HigherAdminsMessage* p);

};

}

namespace server {
enum ServerPacketID { 
    ServerPacketID_Logged = 0,
    ServerPacketID_RemoveDialogs = 1,
    ServerPacketID_RemoveCharDialog = 2,
    ServerPacketID_NavigateToggle = 3,
    ServerPacketID_Disconnect = 4,
    ServerPacketID_CommerceEnd = 5,
    ServerPacketID_BankEnd = 6,
    ServerPacketID_CommerceInit = 7,
    ServerPacketID_BankInit = 8,
    ServerPacketID_UserCommerceInit = 9,
    ServerPacketID_UserCommerceEnd = 10,
    ServerPacketID_UserOfferConfirm = 11,
    ServerPacketID_CommerceChat = 12,
    ServerPacketID_ShowBlacksmithForm = 13,
    ServerPacketID_ShowCarpenterForm = 14,
    ServerPacketID_UpdateSta = 15,
    ServerPacketID_UpdateMana = 16,
    ServerPacketID_UpdateHP = 17,
    ServerPacketID_UpdateGold = 18,
    ServerPacketID_UpdateBankGold = 19,
    ServerPacketID_UpdateExp = 20,
    ServerPacketID_ChangeMap = 21,
    ServerPacketID_PosUpdate = 22,
    ServerPacketID_ChatOverHead = 23,
    ServerPacketID_ConsoleMsg = 24,
    ServerPacketID_GuildChat = 25,
    ServerPacketID_ShowMessageBox = 26,
    ServerPacketID_UserIndexInServer = 27,
    ServerPacketID_UserCharIndexInServer = 28,
    ServerPacketID_CharacterCreate = 29,
    ServerPacketID_CharacterRemove = 30,
    ServerPacketID_CharacterChangeNick = 31,
    ServerPacketID_CharacterMove = 32,
    ServerPacketID_ForceCharMove = 33,
    ServerPacketID_CharacterChange = 34,
    ServerPacketID_ObjectCreate = 35,
    ServerPacketID_ObjectDelete = 36,
    ServerPacketID_BlockPosition = 37,
    ServerPacketID_PlayMidi = 38,
    ServerPacketID_PlayWave = 39,
    ServerPacketID_GuildList = 40,
    ServerPacketID_AreaChanged = 41,
    ServerPacketID_PauseToggle = 42,
    ServerPacketID_RainToggle = 43,
    ServerPacketID_CreateFX = 44,
    ServerPacketID_UpdateUserStats = 45,
    ServerPacketID_WorkRequestTarget = 46,
    ServerPacketID_ChangeInventorySlot = 47,
    ServerPacketID_ChangeBankSlot = 48,
    ServerPacketID_ChangeSpellSlot = 49,
    ServerPacketID_Atributes = 50,
    ServerPacketID_BlacksmithWeapons = 51,
    ServerPacketID_BlacksmithArmors = 52,
    ServerPacketID_CarpenterObjects = 53,
    ServerPacketID_RestOK = 54,
    ServerPacketID_ErrorMsg = 55,
    ServerPacketID_Blind = 56,
    ServerPacketID_Dumb = 57,
    ServerPacketID_ShowSignal = 58,
    ServerPacketID_ChangeNPCInventorySlot = 59,
    ServerPacketID_UpdateHungerAndThirst = 60,
    ServerPacketID_Fame = 61,
    ServerPacketID_MiniStats = 62,
    ServerPacketID_LevelUp = 63,
    ServerPacketID_AddForumMsg = 64,
    ServerPacketID_ShowForumForm = 65,
    ServerPacketID_SetInvisible = 66,
    ServerPacketID_DiceRoll = 67,
    ServerPacketID_MeditateToggle = 68,
    ServerPacketID_BlindNoMore = 69,
    ServerPacketID_DumbNoMore = 70,
    ServerPacketID_SendSkills = 71,
    ServerPacketID_TrainerCreatureList = 72,
    ServerPacketID_GuildNews = 73,
    ServerPacketID_OfferDetails = 74,
    ServerPacketID_AlianceProposalsList = 75,
    ServerPacketID_PeaceProposalsList = 76,
    ServerPacketID_CharacterInfo = 77,
    ServerPacketID_GuildLeaderInfo = 78,
    ServerPacketID_GuildMemberInfo = 79,
    ServerPacketID_GuildDetails = 80,
    ServerPacketID_ShowGuildFundationForm = 81,
    ServerPacketID_ParalizeOK = 82,
    ServerPacketID_ShowUserRequest = 83,
    ServerPacketID_TradeOK = 84,
    ServerPacketID_BankOK = 85,
    ServerPacketID_ChangeUserTradeSlot = 86,
    ServerPacketID_SendNight = 87,
    ServerPacketID_Pong = 88,
    ServerPacketID_UpdateTagAndStatus = 89,
    ServerPacketID_SpawnList = 90,
    ServerPacketID_ShowSOSForm = 91,
    ServerPacketID_ShowMOTDEditionForm = 92,
    ServerPacketID_ShowGMPanelForm = 93,
    ServerPacketID_UserNameList = 94,
    ServerPacketID_ShowDenounces = 95,
    ServerPacketID_RecordList = 96,
    ServerPacketID_RecordDetails = 97,
    ServerPacketID_ShowGuildAlign = 98,
    ServerPacketID_ShowPartyForm = 99,
    ServerPacketID_UpdateStrenghtAndDexterity = 100,
    ServerPacketID_UpdateStrenght = 101,
    ServerPacketID_UpdateDexterity = 102,
    ServerPacketID_AddSlots = 103,
    ServerPacketID_MultiMessage = 104,
    ServerPacketID_StopWorking = 105,
    ServerPacketID_CancelOfferItem = 106,
    ServerPacketID_PACKET_COUNT = 107
};

class ServerPacket : public Packet {
public:
    explicit ServerPacket(int id) : Packet(id) { }
};

ServerPacket* ServerPacketFactory(clsByteQueue* buffer);

void ServerPacketDecodeAndDispatch(clsByteQueue* buffer, PacketHandler* handler);


class Logged : public ServerPacket {
public:
    Logged();
    Logged(clsByteQueue* buffer);
    Logged(std::uint8_t Clase);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Clase; 
};

inline Logged BuildLogged(std::uint8_t Clase) {
    return Logged(Clase);
}

class RemoveDialogs : public ServerPacket {
public:
    RemoveDialogs();
    RemoveDialogs(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RemoveDialogs BuildRemoveDialogs() {
    return RemoveDialogs();
}

class RemoveCharDialog : public ServerPacket {
public:
    RemoveCharDialog();
    RemoveCharDialog(clsByteQueue* buffer);
    RemoveCharDialog(std::int16_t CharIndex);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t CharIndex; 
};

inline RemoveCharDialog BuildRemoveCharDialog(std::int16_t CharIndex) {
    return RemoveCharDialog(CharIndex);
}

class NavigateToggle : public ServerPacket {
public:
    NavigateToggle();
    NavigateToggle(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline NavigateToggle BuildNavigateToggle() {
    return NavigateToggle();
}

class Disconnect : public ServerPacket {
public:
    Disconnect();
    Disconnect(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Disconnect BuildDisconnect() {
    return Disconnect();
}

class CommerceEnd : public ServerPacket {
public:
    CommerceEnd();
    CommerceEnd(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline CommerceEnd BuildCommerceEnd() {
    return CommerceEnd();
}

class BankEnd : public ServerPacket {
public:
    BankEnd();
    BankEnd(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline BankEnd BuildBankEnd() {
    return BankEnd();
}

class CommerceInit : public ServerPacket {
public:
    CommerceInit();
    CommerceInit(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline CommerceInit BuildCommerceInit() {
    return CommerceInit();
}

class BankInit : public ServerPacket {
public:
    BankInit();
    BankInit(clsByteQueue* buffer);
    BankInit(std::int32_t Banco);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int32_t Banco; 
};

inline BankInit BuildBankInit(std::int32_t Banco) {
    return BankInit(Banco);
}

class UserCommerceInit : public ServerPacket {
public:
    UserCommerceInit();
    UserCommerceInit(clsByteQueue* buffer);
    UserCommerceInit(const std::string& DestUserName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string DestUserName; 
};

inline UserCommerceInit BuildUserCommerceInit(const std::string& DestUserName) {
    return UserCommerceInit(DestUserName);
}

class UserCommerceEnd : public ServerPacket {
public:
    UserCommerceEnd();
    UserCommerceEnd(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline UserCommerceEnd BuildUserCommerceEnd() {
    return UserCommerceEnd();
}

class UserOfferConfirm : public ServerPacket {
public:
    UserOfferConfirm();
    UserOfferConfirm(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline UserOfferConfirm BuildUserOfferConfirm() {
    return UserOfferConfirm();
}

class CommerceChat : public ServerPacket {
public:
    CommerceChat();
    CommerceChat(clsByteQueue* buffer);
    CommerceChat(const std::string& Chat, std::uint8_t FontIndex);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Chat; 
    std::uint8_t FontIndex; 
};

inline CommerceChat BuildCommerceChat(const std::string& Chat, std::uint8_t FontIndex) {
    return CommerceChat(Chat, FontIndex);
}

class ShowBlacksmithForm : public ServerPacket {
public:
    ShowBlacksmithForm();
    ShowBlacksmithForm(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ShowBlacksmithForm BuildShowBlacksmithForm() {
    return ShowBlacksmithForm();
}

class ShowCarpenterForm : public ServerPacket {
public:
    ShowCarpenterForm();
    ShowCarpenterForm(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ShowCarpenterForm BuildShowCarpenterForm() {
    return ShowCarpenterForm();
}

class UpdateSta : public ServerPacket {
public:
    UpdateSta();
    UpdateSta(clsByteQueue* buffer);
    UpdateSta(std::int16_t Value);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t Value; 
};

inline UpdateSta BuildUpdateSta(std::int16_t Value) {
    return UpdateSta(Value);
}

class UpdateMana : public ServerPacket {
public:
    UpdateMana();
    UpdateMana(clsByteQueue* buffer);
    UpdateMana(std::int16_t Value);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t Value; 
};

inline UpdateMana BuildUpdateMana(std::int16_t Value) {
    return UpdateMana(Value);
}

class UpdateHP : public ServerPacket {
public:
    UpdateHP();
    UpdateHP(clsByteQueue* buffer);
    UpdateHP(std::int16_t Value);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t Value; 
};

inline UpdateHP BuildUpdateHP(std::int16_t Value) {
    return UpdateHP(Value);
}

class UpdateGold : public ServerPacket {
public:
    UpdateGold();
    UpdateGold(clsByteQueue* buffer);
    UpdateGold(std::int32_t Value);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int32_t Value; 
};

inline UpdateGold BuildUpdateGold(std::int32_t Value) {
    return UpdateGold(Value);
}

class UpdateBankGold : public ServerPacket {
public:
    UpdateBankGold();
    UpdateBankGold(clsByteQueue* buffer);
    UpdateBankGold(std::int32_t Value);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int32_t Value; 
};

inline UpdateBankGold BuildUpdateBankGold(std::int32_t Value) {
    return UpdateBankGold(Value);
}

class UpdateExp : public ServerPacket {
public:
    UpdateExp();
    UpdateExp(clsByteQueue* buffer);
    UpdateExp(std::int32_t Value);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int32_t Value; 
};

inline UpdateExp BuildUpdateExp(std::int32_t Value) {
    return UpdateExp(Value);
}

class ChangeMap : public ServerPacket {
public:
    ChangeMap();
    ChangeMap(clsByteQueue* buffer);
    ChangeMap(std::int16_t Map, std::int16_t Version);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t Map; 
    std::int16_t Version; 
};

inline ChangeMap BuildChangeMap(std::int16_t Map, std::int16_t Version) {
    return ChangeMap(Map, Version);
}

class PosUpdate : public ServerPacket {
public:
    PosUpdate();
    PosUpdate(clsByteQueue* buffer);
    PosUpdate(std::uint8_t X, std::uint8_t Y);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t X; 
    std::uint8_t Y; 
};

inline PosUpdate BuildPosUpdate(std::uint8_t X, std::uint8_t Y) {
    return PosUpdate(X, Y);
}

class ChatOverHead : public ServerPacket {
public:
    ChatOverHead();
    ChatOverHead(clsByteQueue* buffer);
    ChatOverHead(const std::string& Chat, std::int16_t CharIndex, std::uint8_t R, std::uint8_t G, std::uint8_t B);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Chat; 
    std::int16_t CharIndex; 
    std::uint8_t R; 
    std::uint8_t G; 
    std::uint8_t B; 
};

inline ChatOverHead BuildChatOverHead(const std::string& Chat, std::int16_t CharIndex, std::uint8_t R, std::uint8_t G, std::uint8_t B) {
    return ChatOverHead(Chat, CharIndex, R, G, B);
}

class ConsoleMsg : public ServerPacket {
public:
    ConsoleMsg();
    ConsoleMsg(clsByteQueue* buffer);
    ConsoleMsg(const std::string& Chat, std::uint8_t FontIndex);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Chat; 
    std::uint8_t FontIndex; 
};

inline ConsoleMsg BuildConsoleMsg(const std::string& Chat, std::uint8_t FontIndex) {
    return ConsoleMsg(Chat, FontIndex);
}

class GuildChat : public ServerPacket {
public:
    GuildChat();
    GuildChat(clsByteQueue* buffer);
    GuildChat(const std::string& Chat);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Chat; 
};

inline GuildChat BuildGuildChat(const std::string& Chat) {
    return GuildChat(Chat);
}

class ShowMessageBox : public ServerPacket {
public:
    ShowMessageBox();
    ShowMessageBox(clsByteQueue* buffer);
    ShowMessageBox(const std::string& Chat);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Chat; 
};

inline ShowMessageBox BuildShowMessageBox(const std::string& Chat) {
    return ShowMessageBox(Chat);
}

class UserIndexInServer : public ServerPacket {
public:
    UserIndexInServer();
    UserIndexInServer(clsByteQueue* buffer);
    UserIndexInServer(std::int16_t UserIndex);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t UserIndex; 
};

inline UserIndexInServer BuildUserIndexInServer(std::int16_t UserIndex) {
    return UserIndexInServer(UserIndex);
}

class UserCharIndexInServer : public ServerPacket {
public:
    UserCharIndexInServer();
    UserCharIndexInServer(clsByteQueue* buffer);
    UserCharIndexInServer(std::int16_t CharIndex);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t CharIndex; 
};

inline UserCharIndexInServer BuildUserCharIndexInServer(std::int16_t CharIndex) {
    return UserCharIndexInServer(CharIndex);
}

class CharacterCreate : public ServerPacket {
public:
    CharacterCreate();
    CharacterCreate(clsByteQueue* buffer);
    CharacterCreate(std::int16_t CharIndex, std::int16_t Body, std::int16_t Head, std::uint8_t Heading, std::uint8_t X, std::uint8_t Y, std::int16_t Weapon, std::int16_t Shield, std::int16_t Helmet, std::int16_t FX, std::int16_t FXLoops, const std::string& Name, std::uint8_t NickColor, std::uint8_t Privileges);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t CharIndex; 
    std::int16_t Body; 
    std::int16_t Head; 
    std::uint8_t Heading; 
    std::uint8_t X; 
    std::uint8_t Y; 
    std::int16_t Weapon; 
    std::int16_t Shield; 
    std::int16_t Helmet; 
    std::int16_t FX; 
    std::int16_t FXLoops; 
    std::string Name; 
    std::uint8_t NickColor; 
    std::uint8_t Privileges; 
};

inline CharacterCreate BuildCharacterCreate(std::int16_t CharIndex, std::int16_t Body, std::int16_t Head, std::uint8_t Heading, std::uint8_t X, std::uint8_t Y, std::int16_t Weapon, std::int16_t Shield, std::int16_t Helmet, std::int16_t FX, std::int16_t FXLoops, const std::string& Name, std::uint8_t NickColor, std::uint8_t Privileges) {
    return CharacterCreate(CharIndex, Body, Head, Heading, X, Y, Weapon, Shield, Helmet, FX, FXLoops, Name, NickColor, Privileges);
}

class CharacterRemove : public ServerPacket {
public:
    CharacterRemove();
    CharacterRemove(clsByteQueue* buffer);
    CharacterRemove(std::int16_t CharIndex);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t CharIndex; 
};

inline CharacterRemove BuildCharacterRemove(std::int16_t CharIndex) {
    return CharacterRemove(CharIndex);
}

class CharacterChangeNick : public ServerPacket {
public:
    CharacterChangeNick();
    CharacterChangeNick(clsByteQueue* buffer);
    CharacterChangeNick(std::int16_t CharIndex, const std::string& NewName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t CharIndex; 
    std::string NewName; 
};

inline CharacterChangeNick BuildCharacterChangeNick(std::int16_t CharIndex, const std::string& NewName) {
    return CharacterChangeNick(CharIndex, NewName);
}

class CharacterMove : public ServerPacket {
public:
    CharacterMove();
    CharacterMove(clsByteQueue* buffer);
    CharacterMove(std::int16_t CharIndex, std::uint8_t X, std::uint8_t Y);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t CharIndex; 
    std::uint8_t X; 
    std::uint8_t Y; 
};

inline CharacterMove BuildCharacterMove(std::int16_t CharIndex, std::uint8_t X, std::uint8_t Y) {
    return CharacterMove(CharIndex, X, Y);
}

class ForceCharMove : public ServerPacket {
public:
    ForceCharMove();
    ForceCharMove(clsByteQueue* buffer);
    ForceCharMove(std::uint8_t Direction);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Direction; 
};

inline ForceCharMove BuildForceCharMove(std::uint8_t Direction) {
    return ForceCharMove(Direction);
}

class CharacterChange : public ServerPacket {
public:
    CharacterChange();
    CharacterChange(clsByteQueue* buffer);
    CharacterChange(std::int16_t CharIndex, std::int16_t Body, std::int16_t Head, std::uint8_t Heading, std::int16_t Weapon, std::int16_t Shield, std::int16_t Helmet, std::int16_t FX, std::int16_t FXLoops);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t CharIndex; 
    std::int16_t Body; 
    std::int16_t Head; 
    std::uint8_t Heading; 
    std::int16_t Weapon; 
    std::int16_t Shield; 
    std::int16_t Helmet; 
    std::int16_t FX; 
    std::int16_t FXLoops; 
};

inline CharacterChange BuildCharacterChange(std::int16_t CharIndex, std::int16_t Body, std::int16_t Head, std::uint8_t Heading, std::int16_t Weapon, std::int16_t Shield, std::int16_t Helmet, std::int16_t FX, std::int16_t FXLoops) {
    return CharacterChange(CharIndex, Body, Head, Heading, Weapon, Shield, Helmet, FX, FXLoops);
}

class ObjectCreate : public ServerPacket {
public:
    ObjectCreate();
    ObjectCreate(clsByteQueue* buffer);
    ObjectCreate(std::uint8_t X, std::uint8_t Y, std::int16_t GrhIndex);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t X; 
    std::uint8_t Y; 
    std::int16_t GrhIndex; 
};

inline ObjectCreate BuildObjectCreate(std::uint8_t X, std::uint8_t Y, std::int16_t GrhIndex) {
    return ObjectCreate(X, Y, GrhIndex);
}

class ObjectDelete : public ServerPacket {
public:
    ObjectDelete();
    ObjectDelete(clsByteQueue* buffer);
    ObjectDelete(std::uint8_t X, std::uint8_t Y);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t X; 
    std::uint8_t Y; 
};

inline ObjectDelete BuildObjectDelete(std::uint8_t X, std::uint8_t Y) {
    return ObjectDelete(X, Y);
}

class BlockPosition : public ServerPacket {
public:
    BlockPosition();
    BlockPosition(clsByteQueue* buffer);
    BlockPosition(std::uint8_t X, std::uint8_t Y, bool Blocked);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t X; 
    std::uint8_t Y; 
    bool Blocked; 
};

inline BlockPosition BuildBlockPosition(std::uint8_t X, std::uint8_t Y, bool Blocked) {
    return BlockPosition(X, Y, Blocked);
}

class PlayMidi : public ServerPacket {
public:
    PlayMidi();
    PlayMidi(clsByteQueue* buffer);
    PlayMidi(std::int16_t MidiID, std::int16_t Loops);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t MidiID; 
    std::int16_t Loops; 
};

inline PlayMidi BuildPlayMidi(std::int16_t MidiID, std::int16_t Loops) {
    return PlayMidi(MidiID, Loops);
}

class PlayWave : public ServerPacket {
public:
    PlayWave();
    PlayWave(clsByteQueue* buffer);
    PlayWave(std::uint8_t WaveID, std::uint8_t X, std::uint8_t Y);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t WaveID; 
    std::uint8_t X; 
    std::uint8_t Y; 
};

inline PlayWave BuildPlayWave(std::uint8_t WaveID, std::uint8_t X, std::uint8_t Y) {
    return PlayWave(WaveID, X, Y);
}

class GuildList : public ServerPacket {
public:
    GuildList();
    GuildList(clsByteQueue* buffer);
    GuildList(const std::string& Data);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Data; 
};

inline GuildList BuildGuildList(const std::string& Data) {
    return GuildList(Data);
}

class AreaChanged : public ServerPacket {
public:
    AreaChanged();
    AreaChanged(clsByteQueue* buffer);
    AreaChanged(std::uint8_t X, std::uint8_t Y);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t X; 
    std::uint8_t Y; 
};

inline AreaChanged BuildAreaChanged(std::uint8_t X, std::uint8_t Y) {
    return AreaChanged(X, Y);
}

class PauseToggle : public ServerPacket {
public:
    PauseToggle();
    PauseToggle(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline PauseToggle BuildPauseToggle() {
    return PauseToggle();
}

class RainToggle : public ServerPacket {
public:
    RainToggle();
    RainToggle(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RainToggle BuildRainToggle() {
    return RainToggle();
}

class CreateFX : public ServerPacket {
public:
    CreateFX();
    CreateFX(clsByteQueue* buffer);
    CreateFX(std::int16_t CharIndex, std::int16_t FX, std::int16_t FXLoops);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t CharIndex; 
    std::int16_t FX; 
    std::int16_t FXLoops; 
};

inline CreateFX BuildCreateFX(std::int16_t CharIndex, std::int16_t FX, std::int16_t FXLoops) {
    return CreateFX(CharIndex, FX, FXLoops);
}

class UpdateUserStats : public ServerPacket {
public:
    UpdateUserStats();
    UpdateUserStats(clsByteQueue* buffer);
    UpdateUserStats(std::int16_t MaxHp, std::int16_t MinHp, std::int16_t MaxMan, std::int16_t MinMan, std::int16_t MaxSta, std::int16_t MinSta, std::int32_t Gld, std::uint8_t Elv, std::int32_t Elu, std::int32_t Exp);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t MaxHp; 
    std::int16_t MinHp; 
    std::int16_t MaxMan; 
    std::int16_t MinMan; 
    std::int16_t MaxSta; 
    std::int16_t MinSta; 
    std::int32_t Gld; 
    std::uint8_t Elv; 
    std::int32_t Elu; 
    std::int32_t Exp; 
};

inline UpdateUserStats BuildUpdateUserStats(std::int16_t MaxHp, std::int16_t MinHp, std::int16_t MaxMan, std::int16_t MinMan, std::int16_t MaxSta, std::int16_t MinSta, std::int32_t Gld, std::uint8_t Elv, std::int32_t Elu, std::int32_t Exp) {
    return UpdateUserStats(MaxHp, MinHp, MaxMan, MinMan, MaxSta, MinSta, Gld, Elv, Elu, Exp);
}

class WorkRequestTarget : public ServerPacket {
public:
    WorkRequestTarget();
    WorkRequestTarget(clsByteQueue* buffer);
    WorkRequestTarget(std::uint8_t Skill);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Skill; 
};

inline WorkRequestTarget BuildWorkRequestTarget(std::uint8_t Skill) {
    return WorkRequestTarget(Skill);
}

class ChangeInventorySlot : public ServerPacket {
public:
    ChangeInventorySlot();
    ChangeInventorySlot(clsByteQueue* buffer);
    ChangeInventorySlot(std::uint8_t Slot, std::int16_t ObjIndex, const std::string& ObjName, std::int16_t Amount, bool Equiped, std::int16_t GrhIndex, std::uint8_t ObjType, std::int16_t MaxHit, std::int16_t MinHit, std::int16_t MaxDef, std::int16_t MinDef, float ObjSalePrice);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Slot; 
    std::int16_t ObjIndex; 
    std::string ObjName; 
    std::int16_t Amount; 
    bool Equiped; 
    std::int16_t GrhIndex; 
    std::uint8_t ObjType; 
    std::int16_t MaxHit; 
    std::int16_t MinHit; 
    std::int16_t MaxDef; 
    std::int16_t MinDef; 
    float ObjSalePrice; 
};

inline ChangeInventorySlot BuildChangeInventorySlot(std::uint8_t Slot, std::int16_t ObjIndex, const std::string& ObjName, std::int16_t Amount, bool Equiped, std::int16_t GrhIndex, std::uint8_t ObjType, std::int16_t MaxHit, std::int16_t MinHit, std::int16_t MaxDef, std::int16_t MinDef, float ObjSalePrice) {
    return ChangeInventorySlot(Slot, ObjIndex, ObjName, Amount, Equiped, GrhIndex, ObjType, MaxHit, MinHit, MaxDef, MinDef, ObjSalePrice);
}

class ChangeBankSlot : public ServerPacket {
public:
    ChangeBankSlot();
    ChangeBankSlot(clsByteQueue* buffer);
    ChangeBankSlot(std::uint8_t Slot, std::int16_t ObjIndex, const std::string& ObjName, std::int16_t Amount, std::int16_t GrhIndex, std::uint8_t ObjType, std::int16_t MaxHit, std::int16_t MinHit, std::int16_t MaxDef, std::int16_t MinDef, float ObjSalePrice);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Slot; 
    std::int16_t ObjIndex; 
    std::string ObjName; 
    std::int16_t Amount; 
    std::int16_t GrhIndex; 
    std::uint8_t ObjType; 
    std::int16_t MaxHit; 
    std::int16_t MinHit; 
    std::int16_t MaxDef; 
    std::int16_t MinDef; 
    float ObjSalePrice; 
};

inline ChangeBankSlot BuildChangeBankSlot(std::uint8_t Slot, std::int16_t ObjIndex, const std::string& ObjName, std::int16_t Amount, std::int16_t GrhIndex, std::uint8_t ObjType, std::int16_t MaxHit, std::int16_t MinHit, std::int16_t MaxDef, std::int16_t MinDef, float ObjSalePrice) {
    return ChangeBankSlot(Slot, ObjIndex, ObjName, Amount, GrhIndex, ObjType, MaxHit, MinHit, MaxDef, MinDef, ObjSalePrice);
}

class ChangeSpellSlot : public ServerPacket {
public:
    ChangeSpellSlot();
    ChangeSpellSlot(clsByteQueue* buffer);
    ChangeSpellSlot(std::uint8_t Slot, std::int16_t SpellID, const std::string& Name);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Slot; 
    std::int16_t SpellID; 
    std::string Name; 
};

inline ChangeSpellSlot BuildChangeSpellSlot(std::uint8_t Slot, std::int16_t SpellID, const std::string& Name) {
    return ChangeSpellSlot(Slot, SpellID, Name);
}

class Atributes : public ServerPacket {
public:
    Atributes();
    Atributes(clsByteQueue* buffer);
    Atributes(std::uint8_t Fuerza, std::uint8_t Agilidad, std::uint8_t Inteligencia, std::uint8_t Carisma, std::uint8_t Constitucion);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Fuerza; 
    std::uint8_t Agilidad; 
    std::uint8_t Inteligencia; 
    std::uint8_t Carisma; 
    std::uint8_t Constitucion; 
};

inline Atributes BuildAtributes(std::uint8_t Fuerza, std::uint8_t Agilidad, std::uint8_t Inteligencia, std::uint8_t Carisma, std::uint8_t Constitucion) {
    return Atributes(Fuerza, Agilidad, Inteligencia, Carisma, Constitucion);
}

class BlacksmithWeapons : public ServerPacket {
public:
    BlacksmithWeapons();
    BlacksmithWeapons(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    struct Item {
    std::string Name; 
    std::int16_t GrhIndex; 
    std::int16_t LingH; 
    std::int16_t LingP; 
    std::int16_t LingO; 
    std::int16_t ArmasHerreroIndex; 
    std::int16_t ObjUpgrade; 
    };

    std::vector<Item> Items;

    void addItem(const std::string& Name, std::int16_t GrhIndex, std::int16_t LingH, std::int16_t LingP, std::int16_t LingO, std::int16_t ArmasHerreroIndex, std::int16_t ObjUpgrade) {
        Item e;
        e.Name = Name;
        e.GrhIndex = GrhIndex;
        e.LingH = LingH;
        e.LingP = LingP;
        e.LingO = LingO;
        e.ArmasHerreroIndex = ArmasHerreroIndex;
        e.ObjUpgrade = ObjUpgrade;
        Items.push_back(e);
    }
};

class BlacksmithArmors : public ServerPacket {
public:
    BlacksmithArmors();
    BlacksmithArmors(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    struct Item {
    std::string Name; 
    std::int16_t GrhIndex; 
    std::int16_t LingH; 
    std::int16_t LingP; 
    std::int16_t LingO; 
    std::int16_t ArmasHerreroIndex; 
    std::int16_t ObjUpgrade; 
    };

    std::vector<Item> Items;

    void addItem(const std::string& Name, std::int16_t GrhIndex, std::int16_t LingH, std::int16_t LingP, std::int16_t LingO, std::int16_t ArmasHerreroIndex, std::int16_t ObjUpgrade) {
        Item e;
        e.Name = Name;
        e.GrhIndex = GrhIndex;
        e.LingH = LingH;
        e.LingP = LingP;
        e.LingO = LingO;
        e.ArmasHerreroIndex = ArmasHerreroIndex;
        e.ObjUpgrade = ObjUpgrade;
        Items.push_back(e);
    }
};

class CarpenterObjects : public ServerPacket {
public:
    CarpenterObjects();
    CarpenterObjects(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    struct Item {
    std::string Name; 
    std::int16_t GrhIndex; 
    std::int16_t Madera; 
    std::int16_t MaderaElfica; 
    std::int16_t ObjCarpinteroIndex; 
    std::int16_t ObjUpgrade; 
    };

    std::vector<Item> Items;

    void addItem(const std::string& Name, std::int16_t GrhIndex, std::int16_t Madera, std::int16_t MaderaElfica, std::int16_t ObjCarpinteroIndex, std::int16_t ObjUpgrade) {
        Item e;
        e.Name = Name;
        e.GrhIndex = GrhIndex;
        e.Madera = Madera;
        e.MaderaElfica = MaderaElfica;
        e.ObjCarpinteroIndex = ObjCarpinteroIndex;
        e.ObjUpgrade = ObjUpgrade;
        Items.push_back(e);
    }
};

class RestOK : public ServerPacket {
public:
    RestOK();
    RestOK(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RestOK BuildRestOK() {
    return RestOK();
}

class ErrorMsg : public ServerPacket {
public:
    ErrorMsg();
    ErrorMsg(clsByteQueue* buffer);
    ErrorMsg(const std::string& Message);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Message; 
};

inline ErrorMsg BuildErrorMsg(const std::string& Message) {
    return ErrorMsg(Message);
}

class Blind : public ServerPacket {
public:
    Blind();
    Blind(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Blind BuildBlind() {
    return Blind();
}

class Dumb : public ServerPacket {
public:
    Dumb();
    Dumb(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Dumb BuildDumb() {
    return Dumb();
}

class ShowSignal : public ServerPacket {
public:
    ShowSignal();
    ShowSignal(clsByteQueue* buffer);
    ShowSignal(const std::string& Texto, std::int16_t Grh);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Texto; 
    std::int16_t Grh; 
};

inline ShowSignal BuildShowSignal(const std::string& Texto, std::int16_t Grh) {
    return ShowSignal(Texto, Grh);
}

class ChangeNPCInventorySlot : public ServerPacket {
public:
    ChangeNPCInventorySlot();
    ChangeNPCInventorySlot(clsByteQueue* buffer);
    ChangeNPCInventorySlot(std::uint8_t Slot, const std::string& ObjName, std::int16_t Amount, float Price, std::int16_t GrhIndex, std::int16_t ObjIndex, std::uint8_t ObjType, std::int16_t MaxHit, std::int16_t MinHit, std::int16_t MaxDef, std::int16_t MinDef);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Slot; 
    std::string ObjName; 
    std::int16_t Amount; 
    float Price; 
    std::int16_t GrhIndex; 
    std::int16_t ObjIndex; 
    std::uint8_t ObjType; 
    std::int16_t MaxHit; 
    std::int16_t MinHit; 
    std::int16_t MaxDef; 
    std::int16_t MinDef; 
};

inline ChangeNPCInventorySlot BuildChangeNPCInventorySlot(std::uint8_t Slot, const std::string& ObjName, std::int16_t Amount, float Price, std::int16_t GrhIndex, std::int16_t ObjIndex, std::uint8_t ObjType, std::int16_t MaxHit, std::int16_t MinHit, std::int16_t MaxDef, std::int16_t MinDef) {
    return ChangeNPCInventorySlot(Slot, ObjName, Amount, Price, GrhIndex, ObjIndex, ObjType, MaxHit, MinHit, MaxDef, MinDef);
}

class UpdateHungerAndThirst : public ServerPacket {
public:
    UpdateHungerAndThirst();
    UpdateHungerAndThirst(clsByteQueue* buffer);
    UpdateHungerAndThirst(std::uint8_t MaxAgu, std::uint8_t MinAgu, std::uint8_t MaxHam, std::uint8_t MinHam);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t MaxAgu; 
    std::uint8_t MinAgu; 
    std::uint8_t MaxHam; 
    std::uint8_t MinHam; 
};

inline UpdateHungerAndThirst BuildUpdateHungerAndThirst(std::uint8_t MaxAgu, std::uint8_t MinAgu, std::uint8_t MaxHam, std::uint8_t MinHam) {
    return UpdateHungerAndThirst(MaxAgu, MinAgu, MaxHam, MinHam);
}

class Fame : public ServerPacket {
public:
    Fame();
    Fame(clsByteQueue* buffer);
    Fame(std::int32_t Asesino, std::int32_t Bandido, std::int32_t Burgues, std::int32_t Ladron, std::int32_t Noble, std::int32_t Plebe, std::int32_t Promedio);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int32_t Asesino; 
    std::int32_t Bandido; 
    std::int32_t Burgues; 
    std::int32_t Ladron; 
    std::int32_t Noble; 
    std::int32_t Plebe; 
    std::int32_t Promedio; 
};

inline Fame BuildFame(std::int32_t Asesino, std::int32_t Bandido, std::int32_t Burgues, std::int32_t Ladron, std::int32_t Noble, std::int32_t Plebe, std::int32_t Promedio) {
    return Fame(Asesino, Bandido, Burgues, Ladron, Noble, Plebe, Promedio);
}

class MiniStats : public ServerPacket {
public:
    MiniStats();
    MiniStats(clsByteQueue* buffer);
    MiniStats(std::int32_t CiudadanosMatados, std::int32_t CriminalesMatados, std::int32_t UsuariosMatados, std::int16_t NpcsMuertos, std::uint8_t Clase, std::int32_t Pena);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int32_t CiudadanosMatados; 
    std::int32_t CriminalesMatados; 
    std::int32_t UsuariosMatados; 
    std::int16_t NpcsMuertos; 
    std::uint8_t Clase; 
    std::int32_t Pena; 
};

inline MiniStats BuildMiniStats(std::int32_t CiudadanosMatados, std::int32_t CriminalesMatados, std::int32_t UsuariosMatados, std::int16_t NpcsMuertos, std::uint8_t Clase, std::int32_t Pena) {
    return MiniStats(CiudadanosMatados, CriminalesMatados, UsuariosMatados, NpcsMuertos, Clase, Pena);
}

class LevelUp : public ServerPacket {
public:
    LevelUp();
    LevelUp(clsByteQueue* buffer);
    LevelUp(std::int16_t SkillPoints);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t SkillPoints; 
};

inline LevelUp BuildLevelUp(std::int16_t SkillPoints) {
    return LevelUp(SkillPoints);
}

class AddForumMsg : public ServerPacket {
public:
    AddForumMsg();
    AddForumMsg(clsByteQueue* buffer);
    AddForumMsg(std::int32_t ForumType, const std::string& Title, const std::string& Author, const std::string& Message);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int32_t ForumType; 
    std::string Title; 
    std::string Author; 
    std::string Message; 
};

inline AddForumMsg BuildAddForumMsg(std::int32_t ForumType, const std::string& Title, const std::string& Author, const std::string& Message) {
    return AddForumMsg(ForumType, Title, Author, Message);
}

class ShowForumForm : public ServerPacket {
public:
    ShowForumForm();
    ShowForumForm(clsByteQueue* buffer);
    ShowForumForm(std::uint8_t Visibilidad, std::uint8_t CanMakeSticky);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Visibilidad; 
    std::uint8_t CanMakeSticky; 
};

inline ShowForumForm BuildShowForumForm(std::uint8_t Visibilidad, std::uint8_t CanMakeSticky) {
    return ShowForumForm(Visibilidad, CanMakeSticky);
}

class SetInvisible : public ServerPacket {
public:
    SetInvisible();
    SetInvisible(clsByteQueue* buffer);
    SetInvisible(std::int16_t charIndex, bool invisible);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t charIndex; 
    bool invisible; 
};

inline SetInvisible BuildSetInvisible(std::int16_t charIndex, bool invisible) {
    return SetInvisible(charIndex, invisible);
}

class DiceRoll : public ServerPacket {
public:
    DiceRoll();
    DiceRoll(clsByteQueue* buffer);
    DiceRoll(std::uint8_t Fuerza, std::uint8_t Agilidad, std::uint8_t Inteligencia, std::uint8_t Carisma, std::uint8_t Constitucion);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Fuerza; 
    std::uint8_t Agilidad; 
    std::uint8_t Inteligencia; 
    std::uint8_t Carisma; 
    std::uint8_t Constitucion; 
};

inline DiceRoll BuildDiceRoll(std::uint8_t Fuerza, std::uint8_t Agilidad, std::uint8_t Inteligencia, std::uint8_t Carisma, std::uint8_t Constitucion) {
    return DiceRoll(Fuerza, Agilidad, Inteligencia, Carisma, Constitucion);
}

class MeditateToggle : public ServerPacket {
public:
    MeditateToggle();
    MeditateToggle(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline MeditateToggle BuildMeditateToggle() {
    return MeditateToggle();
}

class BlindNoMore : public ServerPacket {
public:
    BlindNoMore();
    BlindNoMore(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline BlindNoMore BuildBlindNoMore() {
    return BlindNoMore();
}

class DumbNoMore : public ServerPacket {
public:
    DumbNoMore();
    DumbNoMore(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline DumbNoMore BuildDumbNoMore() {
    return DumbNoMore();
}

class SendSkills : public ServerPacket {
public:
    SendSkills();
    SendSkills(clsByteQueue* buffer);
    SendSkills(std::vector<std::uint8_t> Skills );

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::vector<std::uint8_t> Skills; 
};

inline SendSkills BuildSendSkills(std::vector<std::uint8_t> Skills ) {
    return SendSkills(Skills);
}

class TrainerCreatureList : public ServerPacket {
public:
    TrainerCreatureList();
    TrainerCreatureList(clsByteQueue* buffer);
    TrainerCreatureList(const std::string& Data);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Data; 
};

inline TrainerCreatureList BuildTrainerCreatureList(const std::string& Data) {
    return TrainerCreatureList(Data);
}

class GuildNews : public ServerPacket {
public:
    GuildNews();
    GuildNews(clsByteQueue* buffer);
    GuildNews(const std::string& News, const std::string& EnemiesList, const std::string& AlliesList);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string News; 
    std::string EnemiesList; 
    std::string AlliesList; 
};

inline GuildNews BuildGuildNews(const std::string& News, const std::string& EnemiesList, const std::string& AlliesList) {
    return GuildNews(News, EnemiesList, AlliesList);
}

class OfferDetails : public ServerPacket {
public:
    OfferDetails();
    OfferDetails(clsByteQueue* buffer);
    OfferDetails(const std::string& Details);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Details; 
};

inline OfferDetails BuildOfferDetails(const std::string& Details) {
    return OfferDetails(Details);
}

class AlianceProposalsList : public ServerPacket {
public:
    AlianceProposalsList();
    AlianceProposalsList(clsByteQueue* buffer);
    AlianceProposalsList(const std::string& Data);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Data; 
};

inline AlianceProposalsList BuildAlianceProposalsList(const std::string& Data) {
    return AlianceProposalsList(Data);
}

class PeaceProposalsList : public ServerPacket {
public:
    PeaceProposalsList();
    PeaceProposalsList(clsByteQueue* buffer);
    PeaceProposalsList(const std::string& Data);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Data; 
};

inline PeaceProposalsList BuildPeaceProposalsList(const std::string& Data) {
    return PeaceProposalsList(Data);
}

class CharacterInfo : public ServerPacket {
public:
    CharacterInfo();
    CharacterInfo(clsByteQueue* buffer);
    CharacterInfo(const std::string& CharName, std::uint8_t Race, std::uint8_t Class, std::uint8_t Gender, std::uint8_t Level, std::int32_t Gold, std::int32_t Bank, std::int32_t Reputation, const std::string& PreviousPetitions, const std::string& CurrentGuild, const std::string& PreviousGuilds, bool RoyalArmy, bool ChaosLegion, std::int32_t CiudadanosMatados, std::int32_t CriminalesMatados);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string CharName; 
    std::uint8_t Race; 
    std::uint8_t Class; 
    std::uint8_t Gender; 
    std::uint8_t Level; 
    std::int32_t Gold; 
    std::int32_t Bank; 
    std::int32_t Reputation; 
    std::string PreviousPetitions; 
    std::string CurrentGuild; 
    std::string PreviousGuilds; 
    bool RoyalArmy; 
    bool ChaosLegion; 
    std::int32_t CiudadanosMatados; 
    std::int32_t CriminalesMatados; 
};

inline CharacterInfo BuildCharacterInfo(const std::string& CharName, std::uint8_t Race, std::uint8_t Class, std::uint8_t Gender, std::uint8_t Level, std::int32_t Gold, std::int32_t Bank, std::int32_t Reputation, const std::string& PreviousPetitions, const std::string& CurrentGuild, const std::string& PreviousGuilds, bool RoyalArmy, bool ChaosLegion, std::int32_t CiudadanosMatados, std::int32_t CriminalesMatados) {
    return CharacterInfo(CharName, Race, Class, Gender, Level, Gold, Bank, Reputation, PreviousPetitions, CurrentGuild, PreviousGuilds, RoyalArmy, ChaosLegion, CiudadanosMatados, CriminalesMatados);
}

class GuildLeaderInfo : public ServerPacket {
public:
    GuildLeaderInfo();
    GuildLeaderInfo(clsByteQueue* buffer);
    GuildLeaderInfo(const std::string& GuildList, const std::string& MemberList, const std::string& GuildNews, const std::string& JoinRequests);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string GuildList; 
    std::string MemberList; 
    std::string GuildNews; 
    std::string JoinRequests; 
};

inline GuildLeaderInfo BuildGuildLeaderInfo(const std::string& GuildList, const std::string& MemberList, const std::string& GuildNews, const std::string& JoinRequests) {
    return GuildLeaderInfo(GuildList, MemberList, GuildNews, JoinRequests);
}

class GuildMemberInfo : public ServerPacket {
public:
    GuildMemberInfo();
    GuildMemberInfo(clsByteQueue* buffer);
    GuildMemberInfo(const std::string& GuildList, const std::string& MemberList);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string GuildList; 
    std::string MemberList; 
};

inline GuildMemberInfo BuildGuildMemberInfo(const std::string& GuildList, const std::string& MemberList) {
    return GuildMemberInfo(GuildList, MemberList);
}

class GuildDetails : public ServerPacket {
public:
    GuildDetails();
    GuildDetails(clsByteQueue* buffer);
    GuildDetails(const std::string& GuildName, const std::string& Founder, const std::string& FoundationDate, const std::string& Leader, const std::string& URL, std::int16_t MemberCount, bool ElectionsOpen, const std::string& Aligment, std::int16_t EnemiesCount, std::int16_t AlliesCount, const std::string& AntifactionPoints, const std::string& Codex, const std::string& GuildDesc);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string GuildName; 
    std::string Founder; 
    std::string FoundationDate; 
    std::string Leader; 
    std::string URL; 
    std::int16_t MemberCount; 
    bool ElectionsOpen; 
    std::string Aligment; 
    std::int16_t EnemiesCount; 
    std::int16_t AlliesCount; 
    std::string AntifactionPoints; 
    std::string Codex; 
    std::string GuildDesc; 
};

inline GuildDetails BuildGuildDetails(const std::string& GuildName, const std::string& Founder, const std::string& FoundationDate, const std::string& Leader, const std::string& URL, std::int16_t MemberCount, bool ElectionsOpen, const std::string& Aligment, std::int16_t EnemiesCount, std::int16_t AlliesCount, const std::string& AntifactionPoints, const std::string& Codex, const std::string& GuildDesc) {
    return GuildDetails(GuildName, Founder, FoundationDate, Leader, URL, MemberCount, ElectionsOpen, Aligment, EnemiesCount, AlliesCount, AntifactionPoints, Codex, GuildDesc);
}

class ShowGuildFundationForm : public ServerPacket {
public:
    ShowGuildFundationForm();
    ShowGuildFundationForm(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ShowGuildFundationForm BuildShowGuildFundationForm() {
    return ShowGuildFundationForm();
}

class ParalizeOK : public ServerPacket {
public:
    ParalizeOK();
    ParalizeOK(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ParalizeOK BuildParalizeOK() {
    return ParalizeOK();
}

class ShowUserRequest : public ServerPacket {
public:
    ShowUserRequest();
    ShowUserRequest(clsByteQueue* buffer);
    ShowUserRequest(const std::string& Details);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Details; 
};

inline ShowUserRequest BuildShowUserRequest(const std::string& Details) {
    return ShowUserRequest(Details);
}

class TradeOK : public ServerPacket {
public:
    TradeOK();
    TradeOK(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline TradeOK BuildTradeOK() {
    return TradeOK();
}

class BankOK : public ServerPacket {
public:
    BankOK();
    BankOK(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline BankOK BuildBankOK() {
    return BankOK();
}

class ChangeUserTradeSlot : public ServerPacket {
public:
    ChangeUserTradeSlot();
    ChangeUserTradeSlot(clsByteQueue* buffer);
    ChangeUserTradeSlot(std::uint8_t OfferSlot, std::int16_t ObjIndex, std::int32_t Amount, std::int16_t GrhIndex, std::uint8_t ObjType, std::int16_t MaxHit, std::int16_t MinHit, std::int16_t MaxDef, std::int16_t MinDef, std::int32_t Price, const std::string& ObjName);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t OfferSlot; 
    std::int16_t ObjIndex; 
    std::int32_t Amount; 
    std::int16_t GrhIndex; 
    std::uint8_t ObjType; 
    std::int16_t MaxHit; 
    std::int16_t MinHit; 
    std::int16_t MaxDef; 
    std::int16_t MinDef; 
    std::int32_t Price; 
    std::string ObjName; 
};

inline ChangeUserTradeSlot BuildChangeUserTradeSlot(std::uint8_t OfferSlot, std::int16_t ObjIndex, std::int32_t Amount, std::int16_t GrhIndex, std::uint8_t ObjType, std::int16_t MaxHit, std::int16_t MinHit, std::int16_t MaxDef, std::int16_t MinDef, std::int32_t Price, const std::string& ObjName) {
    return ChangeUserTradeSlot(OfferSlot, ObjIndex, Amount, GrhIndex, ObjType, MaxHit, MinHit, MaxDef, MinDef, Price, ObjName);
}

class SendNight : public ServerPacket {
public:
    SendNight();
    SendNight(clsByteQueue* buffer);
    SendNight(bool Night);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    bool Night; 
};

inline SendNight BuildSendNight(bool Night) {
    return SendNight(Night);
}

class Pong : public ServerPacket {
public:
    Pong();
    Pong(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Pong BuildPong() {
    return Pong();
}

class UpdateTagAndStatus : public ServerPacket {
public:
    UpdateTagAndStatus();
    UpdateTagAndStatus(clsByteQueue* buffer);
    UpdateTagAndStatus(std::int16_t CharIndex, std::uint8_t NickColor, const std::string& Tag);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t CharIndex; 
    std::uint8_t NickColor; 
    std::string Tag; 
};

inline UpdateTagAndStatus BuildUpdateTagAndStatus(std::int16_t CharIndex, std::uint8_t NickColor, const std::string& Tag) {
    return UpdateTagAndStatus(CharIndex, NickColor, Tag);
}

class SpawnList : public ServerPacket {
public:
    SpawnList();
    SpawnList(clsByteQueue* buffer);
    SpawnList(const std::string& Data);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Data; 
};

inline SpawnList BuildSpawnList(const std::string& Data) {
    return SpawnList(Data);
}

class ShowSOSForm : public ServerPacket {
public:
    ShowSOSForm();
    ShowSOSForm(clsByteQueue* buffer);
    ShowSOSForm(const std::string& Data);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Data; 
};

inline ShowSOSForm BuildShowSOSForm(const std::string& Data) {
    return ShowSOSForm(Data);
}

class ShowMOTDEditionForm : public ServerPacket {
public:
    ShowMOTDEditionForm();
    ShowMOTDEditionForm(clsByteQueue* buffer);
    ShowMOTDEditionForm(const std::string& Data);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Data; 
};

inline ShowMOTDEditionForm BuildShowMOTDEditionForm(const std::string& Data) {
    return ShowMOTDEditionForm(Data);
}

class ShowGMPanelForm : public ServerPacket {
public:
    ShowGMPanelForm();
    ShowGMPanelForm(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ShowGMPanelForm BuildShowGMPanelForm() {
    return ShowGMPanelForm();
}

class UserNameList : public ServerPacket {
public:
    UserNameList();
    UserNameList(clsByteQueue* buffer);
    UserNameList(const std::string& Data);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Data; 
};

inline UserNameList BuildUserNameList(const std::string& Data) {
    return UserNameList(Data);
}

class ShowDenounces : public ServerPacket {
public:
    ShowDenounces();
    ShowDenounces(clsByteQueue* buffer);
    ShowDenounces(const std::string& Data);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Data; 
};

inline ShowDenounces BuildShowDenounces(const std::string& Data) {
    return ShowDenounces(Data);
}

class RecordList : public ServerPacket {
public:
    RecordList();
    RecordList(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    struct Item {
    std::string Usuario; 
    };

    std::vector<Item> Items;

    void addItem(const std::string& Usuario) {
        Item e;
        e.Usuario = Usuario;
        Items.push_back(e);
    }
};

class RecordDetails : public ServerPacket {
public:
    RecordDetails();
    RecordDetails(clsByteQueue* buffer);
    RecordDetails(const std::string& Creador, const std::string& Motivo, bool Online, const std::string& IP, const std::string& OnlineTime, const std::string& Obs);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Creador; 
    std::string Motivo; 
    bool Online; 
    std::string IP; 
    std::string OnlineTime; 
    std::string Obs; 
};

inline RecordDetails BuildRecordDetails(const std::string& Creador, const std::string& Motivo, bool Online, const std::string& IP, const std::string& OnlineTime, const std::string& Obs) {
    return RecordDetails(Creador, Motivo, Online, IP, OnlineTime, Obs);
}

class ShowGuildAlign : public ServerPacket {
public:
    ShowGuildAlign();
    ShowGuildAlign(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ShowGuildAlign BuildShowGuildAlign() {
    return ShowGuildAlign();
}

class ShowPartyForm : public ServerPacket {
public:
    ShowPartyForm();
    ShowPartyForm(clsByteQueue* buffer);
    ShowPartyForm(std::uint8_t EsLider, const std::string& Data, std::int32_t Exp);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t EsLider; 
    std::string Data; 
    std::int32_t Exp; 
};

inline ShowPartyForm BuildShowPartyForm(std::uint8_t EsLider, const std::string& Data, std::int32_t Exp) {
    return ShowPartyForm(EsLider, Data, Exp);
}

class UpdateStrenghtAndDexterity : public ServerPacket {
public:
    UpdateStrenghtAndDexterity();
    UpdateStrenghtAndDexterity(clsByteQueue* buffer);
    UpdateStrenghtAndDexterity(std::uint8_t Fuerza, std::uint8_t Agilidad);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Fuerza; 
    std::uint8_t Agilidad; 
};

inline UpdateStrenghtAndDexterity BuildUpdateStrenghtAndDexterity(std::uint8_t Fuerza, std::uint8_t Agilidad) {
    return UpdateStrenghtAndDexterity(Fuerza, Agilidad);
}

class UpdateStrenght : public ServerPacket {
public:
    UpdateStrenght();
    UpdateStrenght(clsByteQueue* buffer);
    UpdateStrenght(std::uint8_t Fuerza);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Fuerza; 
};

inline UpdateStrenght BuildUpdateStrenght(std::uint8_t Fuerza) {
    return UpdateStrenght(Fuerza);
}

class UpdateDexterity : public ServerPacket {
public:
    UpdateDexterity();
    UpdateDexterity(clsByteQueue* buffer);
    UpdateDexterity(std::uint8_t Agilidad);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Agilidad; 
};

inline UpdateDexterity BuildUpdateDexterity(std::uint8_t Agilidad) {
    return UpdateDexterity(Agilidad);
}

class AddSlots : public ServerPacket {
public:
    AddSlots();
    AddSlots(clsByteQueue* buffer);
    AddSlots(std::uint8_t Mochila);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Mochila; 
};

inline AddSlots BuildAddSlots(std::uint8_t Mochila) {
    return AddSlots(Mochila);
}

class MultiMessage : public ServerPacket {
public:
    MultiMessage();
    MultiMessage(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline MultiMessage BuildMultiMessage() {
    return MultiMessage();
}

class StopWorking : public ServerPacket {
public:
    StopWorking();
    StopWorking(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline StopWorking BuildStopWorking() {
    return StopWorking();
}

class CancelOfferItem : public ServerPacket {
public:
    CancelOfferItem();
    CancelOfferItem(clsByteQueue* buffer);
    CancelOfferItem(std::uint8_t Slot);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Slot; 
};

inline CancelOfferItem BuildCancelOfferItem(std::uint8_t Slot) {
    return CancelOfferItem(Slot);
}

class ServerPacketHandler {
public:
    virtual ~ServerPacketHandler();

    virtual void handleLogged(Logged* p);
    virtual void handleRemoveDialogs(RemoveDialogs* p);
    virtual void handleRemoveCharDialog(RemoveCharDialog* p);
    virtual void handleNavigateToggle(NavigateToggle* p);
    virtual void handleDisconnect(Disconnect* p);
    virtual void handleCommerceEnd(CommerceEnd* p);
    virtual void handleBankEnd(BankEnd* p);
    virtual void handleCommerceInit(CommerceInit* p);
    virtual void handleBankInit(BankInit* p);
    virtual void handleUserCommerceInit(UserCommerceInit* p);
    virtual void handleUserCommerceEnd(UserCommerceEnd* p);
    virtual void handleUserOfferConfirm(UserOfferConfirm* p);
    virtual void handleCommerceChat(CommerceChat* p);
    virtual void handleShowBlacksmithForm(ShowBlacksmithForm* p);
    virtual void handleShowCarpenterForm(ShowCarpenterForm* p);
    virtual void handleUpdateSta(UpdateSta* p);
    virtual void handleUpdateMana(UpdateMana* p);
    virtual void handleUpdateHP(UpdateHP* p);
    virtual void handleUpdateGold(UpdateGold* p);
    virtual void handleUpdateBankGold(UpdateBankGold* p);
    virtual void handleUpdateExp(UpdateExp* p);
    virtual void handleChangeMap(ChangeMap* p);
    virtual void handlePosUpdate(PosUpdate* p);
    virtual void handleChatOverHead(ChatOverHead* p);
    virtual void handleConsoleMsg(ConsoleMsg* p);
    virtual void handleGuildChat(GuildChat* p);
    virtual void handleShowMessageBox(ShowMessageBox* p);
    virtual void handleUserIndexInServer(UserIndexInServer* p);
    virtual void handleUserCharIndexInServer(UserCharIndexInServer* p);
    virtual void handleCharacterCreate(CharacterCreate* p);
    virtual void handleCharacterRemove(CharacterRemove* p);
    virtual void handleCharacterChangeNick(CharacterChangeNick* p);
    virtual void handleCharacterMove(CharacterMove* p);
    virtual void handleForceCharMove(ForceCharMove* p);
    virtual void handleCharacterChange(CharacterChange* p);
    virtual void handleObjectCreate(ObjectCreate* p);
    virtual void handleObjectDelete(ObjectDelete* p);
    virtual void handleBlockPosition(BlockPosition* p);
    virtual void handlePlayMidi(PlayMidi* p);
    virtual void handlePlayWave(PlayWave* p);
    virtual void handleGuildList(GuildList* p);
    virtual void handleAreaChanged(AreaChanged* p);
    virtual void handlePauseToggle(PauseToggle* p);
    virtual void handleRainToggle(RainToggle* p);
    virtual void handleCreateFX(CreateFX* p);
    virtual void handleUpdateUserStats(UpdateUserStats* p);
    virtual void handleWorkRequestTarget(WorkRequestTarget* p);
    virtual void handleChangeInventorySlot(ChangeInventorySlot* p);
    virtual void handleChangeBankSlot(ChangeBankSlot* p);
    virtual void handleChangeSpellSlot(ChangeSpellSlot* p);
    virtual void handleAtributes(Atributes* p);
    virtual void handleBlacksmithWeapons(BlacksmithWeapons* p);
    virtual void handleBlacksmithArmors(BlacksmithArmors* p);
    virtual void handleCarpenterObjects(CarpenterObjects* p);
    virtual void handleRestOK(RestOK* p);
    virtual void handleErrorMsg(ErrorMsg* p);
    virtual void handleBlind(Blind* p);
    virtual void handleDumb(Dumb* p);
    virtual void handleShowSignal(ShowSignal* p);
    virtual void handleChangeNPCInventorySlot(ChangeNPCInventorySlot* p);
    virtual void handleUpdateHungerAndThirst(UpdateHungerAndThirst* p);
    virtual void handleFame(Fame* p);
    virtual void handleMiniStats(MiniStats* p);
    virtual void handleLevelUp(LevelUp* p);
    virtual void handleAddForumMsg(AddForumMsg* p);
    virtual void handleShowForumForm(ShowForumForm* p);
    virtual void handleSetInvisible(SetInvisible* p);
    virtual void handleDiceRoll(DiceRoll* p);
    virtual void handleMeditateToggle(MeditateToggle* p);
    virtual void handleBlindNoMore(BlindNoMore* p);
    virtual void handleDumbNoMore(DumbNoMore* p);
    virtual void handleSendSkills(SendSkills* p);
    virtual void handleTrainerCreatureList(TrainerCreatureList* p);
    virtual void handleGuildNews(GuildNews* p);
    virtual void handleOfferDetails(OfferDetails* p);
    virtual void handleAlianceProposalsList(AlianceProposalsList* p);
    virtual void handlePeaceProposalsList(PeaceProposalsList* p);
    virtual void handleCharacterInfo(CharacterInfo* p);
    virtual void handleGuildLeaderInfo(GuildLeaderInfo* p);
    virtual void handleGuildMemberInfo(GuildMemberInfo* p);
    virtual void handleGuildDetails(GuildDetails* p);
    virtual void handleShowGuildFundationForm(ShowGuildFundationForm* p);
    virtual void handleParalizeOK(ParalizeOK* p);
    virtual void handleShowUserRequest(ShowUserRequest* p);
    virtual void handleTradeOK(TradeOK* p);
    virtual void handleBankOK(BankOK* p);
    virtual void handleChangeUserTradeSlot(ChangeUserTradeSlot* p);
    virtual void handleSendNight(SendNight* p);
    virtual void handlePong(Pong* p);
    virtual void handleUpdateTagAndStatus(UpdateTagAndStatus* p);
    virtual void handleSpawnList(SpawnList* p);
    virtual void handleShowSOSForm(ShowSOSForm* p);
    virtual void handleShowMOTDEditionForm(ShowMOTDEditionForm* p);
    virtual void handleShowGMPanelForm(ShowGMPanelForm* p);
    virtual void handleUserNameList(UserNameList* p);
    virtual void handleShowDenounces(ShowDenounces* p);
    virtual void handleRecordList(RecordList* p);
    virtual void handleRecordDetails(RecordDetails* p);
    virtual void handleShowGuildAlign(ShowGuildAlign* p);
    virtual void handleShowPartyForm(ShowPartyForm* p);
    virtual void handleUpdateStrenghtAndDexterity(UpdateStrenghtAndDexterity* p);
    virtual void handleUpdateStrenght(UpdateStrenght* p);
    virtual void handleUpdateDexterity(UpdateDexterity* p);
    virtual void handleAddSlots(AddSlots* p);
    virtual void handleMultiMessage(MultiMessage* p);
    virtual void handleStopWorking(StopWorking* p);
    virtual void handleCancelOfferItem(CancelOfferItem* p);

};

}

}
}

#endif

