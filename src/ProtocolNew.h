
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

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::string Password; 
    std::uint8_t VerA; 
    std::uint8_t VerB; 
    std::uint8_t VerC; 
};

inline LoginExistingChar BuildLoginExistingChar(const std::string& UserName, const std::string& Password, std::uint8_t VerA, std::uint8_t VerB, std::uint8_t VerC) {
    LoginExistingChar e;
        e.UserName = UserName;
        e.Password = Password;
        e.VerA = VerA;
        e.VerB = VerB;
        e.VerC = VerC;
    return e;
}

class ThrowDices : public ClientPacket {
public:
    ThrowDices();
    ThrowDices(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ThrowDices BuildThrowDices() {
    ThrowDices e;

    return e;
}

class LoginNewChar : public ClientPacket {
public:
    LoginNewChar();
    LoginNewChar(clsByteQueue* buffer);

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
    LoginNewChar e;
        e.UserName = UserName;
        e.Password = Password;
        e.VerA = VerA;
        e.VerB = VerB;
        e.VerC = VerC;
        e.Race = Race;
        e.Gender = Gender;
        e.Class = Class;
        e.Head = Head;
        e.Mail = Mail;
        e.Homeland = Homeland;
    return e;
}

class Talk : public ClientPacket {
public:
    Talk();
    Talk(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Chat; 
};

inline Talk BuildTalk(const std::string& Chat) {
    Talk e;
        e.Chat = Chat;
    return e;
}

class Yell : public ClientPacket {
public:
    Yell();
    Yell(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Chat; 
};

inline Yell BuildYell(const std::string& Chat) {
    Yell e;
        e.Chat = Chat;
    return e;
}

class Whisper : public ClientPacket {
public:
    Whisper();
    Whisper(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string TargetName; 
    std::string Chat; 
};

inline Whisper BuildWhisper(const std::string& TargetName, const std::string& Chat) {
    Whisper e;
        e.TargetName = TargetName;
        e.Chat = Chat;
    return e;
}

class Walk : public ClientPacket {
public:
    Walk();
    Walk(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Heading; 
};

inline Walk BuildWalk(std::uint8_t Heading) {
    Walk e;
        e.Heading = Heading;
    return e;
}

class RequestPositionUpdate : public ClientPacket {
public:
    RequestPositionUpdate();
    RequestPositionUpdate(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RequestPositionUpdate BuildRequestPositionUpdate() {
    RequestPositionUpdate e;

    return e;
}

class Attack : public ClientPacket {
public:
    Attack();
    Attack(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Attack BuildAttack() {
    Attack e;

    return e;
}

class PickUp : public ClientPacket {
public:
    PickUp();
    PickUp(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline PickUp BuildPickUp() {
    PickUp e;

    return e;
}

class SafeToggle : public ClientPacket {
public:
    SafeToggle();
    SafeToggle(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline SafeToggle BuildSafeToggle() {
    SafeToggle e;

    return e;
}

class ResuscitationSafeToggle : public ClientPacket {
public:
    ResuscitationSafeToggle();
    ResuscitationSafeToggle(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ResuscitationSafeToggle BuildResuscitationSafeToggle() {
    ResuscitationSafeToggle e;

    return e;
}

class RequestGuildLeaderInfo : public ClientPacket {
public:
    RequestGuildLeaderInfo();
    RequestGuildLeaderInfo(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RequestGuildLeaderInfo BuildRequestGuildLeaderInfo() {
    RequestGuildLeaderInfo e;

    return e;
}

class RequestAtributes : public ClientPacket {
public:
    RequestAtributes();
    RequestAtributes(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RequestAtributes BuildRequestAtributes() {
    RequestAtributes e;

    return e;
}

class RequestFame : public ClientPacket {
public:
    RequestFame();
    RequestFame(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RequestFame BuildRequestFame() {
    RequestFame e;

    return e;
}

class RequestSkills : public ClientPacket {
public:
    RequestSkills();
    RequestSkills(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RequestSkills BuildRequestSkills() {
    RequestSkills e;

    return e;
}

class RequestMiniStats : public ClientPacket {
public:
    RequestMiniStats();
    RequestMiniStats(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RequestMiniStats BuildRequestMiniStats() {
    RequestMiniStats e;

    return e;
}

class CommerceEnd : public ClientPacket {
public:
    CommerceEnd();
    CommerceEnd(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline CommerceEnd BuildCommerceEnd() {
    CommerceEnd e;

    return e;
}

class UserCommerceEnd : public ClientPacket {
public:
    UserCommerceEnd();
    UserCommerceEnd(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline UserCommerceEnd BuildUserCommerceEnd() {
    UserCommerceEnd e;

    return e;
}

class UserCommerceConfirm : public ClientPacket {
public:
    UserCommerceConfirm();
    UserCommerceConfirm(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline UserCommerceConfirm BuildUserCommerceConfirm() {
    UserCommerceConfirm e;

    return e;
}

class CommerceChat : public ClientPacket {
public:
    CommerceChat();
    CommerceChat(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Chat; 
};

inline CommerceChat BuildCommerceChat(const std::string& Chat) {
    CommerceChat e;
        e.Chat = Chat;
    return e;
}

class BankEnd : public ClientPacket {
public:
    BankEnd();
    BankEnd(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline BankEnd BuildBankEnd() {
    BankEnd e;

    return e;
}

class UserCommerceOk : public ClientPacket {
public:
    UserCommerceOk();
    UserCommerceOk(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline UserCommerceOk BuildUserCommerceOk() {
    UserCommerceOk e;

    return e;
}

class UserCommerceReject : public ClientPacket {
public:
    UserCommerceReject();
    UserCommerceReject(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline UserCommerceReject BuildUserCommerceReject() {
    UserCommerceReject e;

    return e;
}

class Drop : public ClientPacket {
public:
    Drop();
    Drop(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Slot; 
    std::int16_t Amount; 
};

inline Drop BuildDrop(std::uint8_t Slot, std::int16_t Amount) {
    Drop e;
        e.Slot = Slot;
        e.Amount = Amount;
    return e;
}

class CastSpell : public ClientPacket {
public:
    CastSpell();
    CastSpell(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Spell; 
};

inline CastSpell BuildCastSpell(std::uint8_t Spell) {
    CastSpell e;
        e.Spell = Spell;
    return e;
}

class LeftClick : public ClientPacket {
public:
    LeftClick();
    LeftClick(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t X; 
    std::uint8_t Y; 
};

inline LeftClick BuildLeftClick(std::uint8_t X, std::uint8_t Y) {
    LeftClick e;
        e.X = X;
        e.Y = Y;
    return e;
}

class DoubleClick : public ClientPacket {
public:
    DoubleClick();
    DoubleClick(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t X; 
    std::uint8_t Y; 
};

inline DoubleClick BuildDoubleClick(std::uint8_t X, std::uint8_t Y) {
    DoubleClick e;
        e.X = X;
        e.Y = Y;
    return e;
}

class Work : public ClientPacket {
public:
    Work();
    Work(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Skill; 
};

inline Work BuildWork(std::uint8_t Skill) {
    Work e;
        e.Skill = Skill;
    return e;
}

class UseSpellMacro : public ClientPacket {
public:
    UseSpellMacro();
    UseSpellMacro(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline UseSpellMacro BuildUseSpellMacro() {
    UseSpellMacro e;

    return e;
}

class UseItem : public ClientPacket {
public:
    UseItem();
    UseItem(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Slot; 
};

inline UseItem BuildUseItem(std::uint8_t Slot) {
    UseItem e;
        e.Slot = Slot;
    return e;
}

class CraftBlacksmith : public ClientPacket {
public:
    CraftBlacksmith();
    CraftBlacksmith(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t Item; 
};

inline CraftBlacksmith BuildCraftBlacksmith(std::int16_t Item) {
    CraftBlacksmith e;
        e.Item = Item;
    return e;
}

class CraftCarpenter : public ClientPacket {
public:
    CraftCarpenter();
    CraftCarpenter(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t Item; 
};

inline CraftCarpenter BuildCraftCarpenter(std::int16_t Item) {
    CraftCarpenter e;
        e.Item = Item;
    return e;
}

class WorkLeftClick : public ClientPacket {
public:
    WorkLeftClick();
    WorkLeftClick(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t X; 
    std::uint8_t Y; 
    std::uint8_t Skill; 
};

inline WorkLeftClick BuildWorkLeftClick(std::uint8_t X, std::uint8_t Y, std::uint8_t Skill) {
    WorkLeftClick e;
        e.X = X;
        e.Y = Y;
        e.Skill = Skill;
    return e;
}

class CreateNewGuild : public ClientPacket {
public:
    CreateNewGuild();
    CreateNewGuild(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Desc; 
    std::string GuildName; 
    std::string Site; 
    std::string Codex; 
};

inline CreateNewGuild BuildCreateNewGuild(const std::string& Desc, const std::string& GuildName, const std::string& Site, const std::string& Codex) {
    CreateNewGuild e;
        e.Desc = Desc;
        e.GuildName = GuildName;
        e.Site = Site;
        e.Codex = Codex;
    return e;
}

class SpellInfo : public ClientPacket {
public:
    SpellInfo();
    SpellInfo(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Slot; 
};

inline SpellInfo BuildSpellInfo(std::uint8_t Slot) {
    SpellInfo e;
        e.Slot = Slot;
    return e;
}

class EquipItem : public ClientPacket {
public:
    EquipItem();
    EquipItem(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Slot; 
};

inline EquipItem BuildEquipItem(std::uint8_t Slot) {
    EquipItem e;
        e.Slot = Slot;
    return e;
}

class ChangeHeading : public ClientPacket {
public:
    ChangeHeading();
    ChangeHeading(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Heading; 
};

inline ChangeHeading BuildChangeHeading(std::uint8_t Heading) {
    ChangeHeading e;
        e.Heading = Heading;
    return e;
}

class ModifySkills : public ClientPacket {
public:
    ModifySkills();
    ModifySkills(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::vector<std::uint8_t> Skills; 
};

inline ModifySkills BuildModifySkills(std::vector<std::uint8_t> Skills ) {
    ModifySkills e;
        e.Skills = Skills;
    return e;
}

class Train : public ClientPacket {
public:
    Train();
    Train(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t PetIndex; 
};

inline Train BuildTrain(std::uint8_t PetIndex) {
    Train e;
        e.PetIndex = PetIndex;
    return e;
}

class CommerceBuy : public ClientPacket {
public:
    CommerceBuy();
    CommerceBuy(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Slot; 
    std::int16_t Amount; 
};

inline CommerceBuy BuildCommerceBuy(std::uint8_t Slot, std::int16_t Amount) {
    CommerceBuy e;
        e.Slot = Slot;
        e.Amount = Amount;
    return e;
}

class BankExtractItem : public ClientPacket {
public:
    BankExtractItem();
    BankExtractItem(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Slot; 
    std::int16_t Amount; 
};

inline BankExtractItem BuildBankExtractItem(std::uint8_t Slot, std::int16_t Amount) {
    BankExtractItem e;
        e.Slot = Slot;
        e.Amount = Amount;
    return e;
}

class CommerceSell : public ClientPacket {
public:
    CommerceSell();
    CommerceSell(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Slot; 
    std::int16_t Amount; 
};

inline CommerceSell BuildCommerceSell(std::uint8_t Slot, std::int16_t Amount) {
    CommerceSell e;
        e.Slot = Slot;
        e.Amount = Amount;
    return e;
}

class BankDeposit : public ClientPacket {
public:
    BankDeposit();
    BankDeposit(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Slot; 
    std::int16_t Amount; 
};

inline BankDeposit BuildBankDeposit(std::uint8_t Slot, std::int16_t Amount) {
    BankDeposit e;
        e.Slot = Slot;
        e.Amount = Amount;
    return e;
}

class ForumPost : public ClientPacket {
public:
    ForumPost();
    ForumPost(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t MsgType; 
    std::string Title; 
    std::string Post; 
};

inline ForumPost BuildForumPost(std::uint8_t MsgType, const std::string& Title, const std::string& Post) {
    ForumPost e;
        e.MsgType = MsgType;
        e.Title = Title;
        e.Post = Post;
    return e;
}

class MoveSpell : public ClientPacket {
public:
    MoveSpell();
    MoveSpell(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    bool Direction; 
    std::uint8_t Slot; 
};

inline MoveSpell BuildMoveSpell(bool Direction, std::uint8_t Slot) {
    MoveSpell e;
        e.Direction = Direction;
        e.Slot = Slot;
    return e;
}

class MoveBank : public ClientPacket {
public:
    MoveBank();
    MoveBank(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    bool Direction; 
    std::uint8_t Slot; 
};

inline MoveBank BuildMoveBank(bool Direction, std::uint8_t Slot) {
    MoveBank e;
        e.Direction = Direction;
        e.Slot = Slot;
    return e;
}

class ClanCodexUpdate : public ClientPacket {
public:
    ClanCodexUpdate();
    ClanCodexUpdate(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Desc; 
    std::string Codex; 
};

inline ClanCodexUpdate BuildClanCodexUpdate(const std::string& Desc, const std::string& Codex) {
    ClanCodexUpdate e;
        e.Desc = Desc;
        e.Codex = Codex;
    return e;
}

class UserCommerceOffer : public ClientPacket {
public:
    UserCommerceOffer();
    UserCommerceOffer(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Slot; 
    std::int32_t Amount; 
    std::uint8_t OfferSlot; 
};

inline UserCommerceOffer BuildUserCommerceOffer(std::uint8_t Slot, std::int32_t Amount, std::uint8_t OfferSlot) {
    UserCommerceOffer e;
        e.Slot = Slot;
        e.Amount = Amount;
        e.OfferSlot = OfferSlot;
    return e;
}

class GuildAcceptPeace : public ClientPacket {
public:
    GuildAcceptPeace();
    GuildAcceptPeace(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Guild; 
};

inline GuildAcceptPeace BuildGuildAcceptPeace(const std::string& Guild) {
    GuildAcceptPeace e;
        e.Guild = Guild;
    return e;
}

class GuildRejectAlliance : public ClientPacket {
public:
    GuildRejectAlliance();
    GuildRejectAlliance(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Guild; 
};

inline GuildRejectAlliance BuildGuildRejectAlliance(const std::string& Guild) {
    GuildRejectAlliance e;
        e.Guild = Guild;
    return e;
}

class GuildRejectPeace : public ClientPacket {
public:
    GuildRejectPeace();
    GuildRejectPeace(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Guild; 
};

inline GuildRejectPeace BuildGuildRejectPeace(const std::string& Guild) {
    GuildRejectPeace e;
        e.Guild = Guild;
    return e;
}

class GuildAcceptAlliance : public ClientPacket {
public:
    GuildAcceptAlliance();
    GuildAcceptAlliance(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Guild; 
};

inline GuildAcceptAlliance BuildGuildAcceptAlliance(const std::string& Guild) {
    GuildAcceptAlliance e;
        e.Guild = Guild;
    return e;
}

class GuildOfferPeace : public ClientPacket {
public:
    GuildOfferPeace();
    GuildOfferPeace(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Guild; 
    std::string Proposal; 
};

inline GuildOfferPeace BuildGuildOfferPeace(const std::string& Guild, const std::string& Proposal) {
    GuildOfferPeace e;
        e.Guild = Guild;
        e.Proposal = Proposal;
    return e;
}

class GuildOfferAlliance : public ClientPacket {
public:
    GuildOfferAlliance();
    GuildOfferAlliance(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Guild; 
    std::string Proposal; 
};

inline GuildOfferAlliance BuildGuildOfferAlliance(const std::string& Guild, const std::string& Proposal) {
    GuildOfferAlliance e;
        e.Guild = Guild;
        e.Proposal = Proposal;
    return e;
}

class GuildAllianceDetails : public ClientPacket {
public:
    GuildAllianceDetails();
    GuildAllianceDetails(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Guild; 
};

inline GuildAllianceDetails BuildGuildAllianceDetails(const std::string& Guild) {
    GuildAllianceDetails e;
        e.Guild = Guild;
    return e;
}

class GuildPeaceDetails : public ClientPacket {
public:
    GuildPeaceDetails();
    GuildPeaceDetails(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Guild; 
};

inline GuildPeaceDetails BuildGuildPeaceDetails(const std::string& Guild) {
    GuildPeaceDetails e;
        e.Guild = Guild;
    return e;
}

class GuildRequestJoinerInfo : public ClientPacket {
public:
    GuildRequestJoinerInfo();
    GuildRequestJoinerInfo(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string User; 
};

inline GuildRequestJoinerInfo BuildGuildRequestJoinerInfo(const std::string& User) {
    GuildRequestJoinerInfo e;
        e.User = User;
    return e;
}

class GuildAlliancePropList : public ClientPacket {
public:
    GuildAlliancePropList();
    GuildAlliancePropList(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline GuildAlliancePropList BuildGuildAlliancePropList() {
    GuildAlliancePropList e;

    return e;
}

class GuildPeacePropList : public ClientPacket {
public:
    GuildPeacePropList();
    GuildPeacePropList(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline GuildPeacePropList BuildGuildPeacePropList() {
    GuildPeacePropList e;

    return e;
}

class GuildDeclareWar : public ClientPacket {
public:
    GuildDeclareWar();
    GuildDeclareWar(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Guild; 
};

inline GuildDeclareWar BuildGuildDeclareWar(const std::string& Guild) {
    GuildDeclareWar e;
        e.Guild = Guild;
    return e;
}

class GuildNewWebsite : public ClientPacket {
public:
    GuildNewWebsite();
    GuildNewWebsite(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Website; 
};

inline GuildNewWebsite BuildGuildNewWebsite(const std::string& Website) {
    GuildNewWebsite e;
        e.Website = Website;
    return e;
}

class GuildAcceptNewMember : public ClientPacket {
public:
    GuildAcceptNewMember();
    GuildAcceptNewMember(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline GuildAcceptNewMember BuildGuildAcceptNewMember(const std::string& UserName) {
    GuildAcceptNewMember e;
        e.UserName = UserName;
    return e;
}

class GuildRejectNewMember : public ClientPacket {
public:
    GuildRejectNewMember();
    GuildRejectNewMember(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::string Reason; 
};

inline GuildRejectNewMember BuildGuildRejectNewMember(const std::string& UserName, const std::string& Reason) {
    GuildRejectNewMember e;
        e.UserName = UserName;
        e.Reason = Reason;
    return e;
}

class GuildKickMember : public ClientPacket {
public:
    GuildKickMember();
    GuildKickMember(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline GuildKickMember BuildGuildKickMember(const std::string& UserName) {
    GuildKickMember e;
        e.UserName = UserName;
    return e;
}

class GuildUpdateNews : public ClientPacket {
public:
    GuildUpdateNews();
    GuildUpdateNews(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string News; 
};

inline GuildUpdateNews BuildGuildUpdateNews(const std::string& News) {
    GuildUpdateNews e;
        e.News = News;
    return e;
}

class GuildMemberInfo : public ClientPacket {
public:
    GuildMemberInfo();
    GuildMemberInfo(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline GuildMemberInfo BuildGuildMemberInfo(const std::string& UserName) {
    GuildMemberInfo e;
        e.UserName = UserName;
    return e;
}

class GuildOpenElections : public ClientPacket {
public:
    GuildOpenElections();
    GuildOpenElections(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline GuildOpenElections BuildGuildOpenElections() {
    GuildOpenElections e;

    return e;
}

class GuildRequestMembership : public ClientPacket {
public:
    GuildRequestMembership();
    GuildRequestMembership(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Guild; 
    std::string Application; 
};

inline GuildRequestMembership BuildGuildRequestMembership(const std::string& Guild, const std::string& Application) {
    GuildRequestMembership e;
        e.Guild = Guild;
        e.Application = Application;
    return e;
}

class GuildRequestDetails : public ClientPacket {
public:
    GuildRequestDetails();
    GuildRequestDetails(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Guild; 
};

inline GuildRequestDetails BuildGuildRequestDetails(const std::string& Guild) {
    GuildRequestDetails e;
        e.Guild = Guild;
    return e;
}

class Online : public ClientPacket {
public:
    Online();
    Online(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Online BuildOnline() {
    Online e;

    return e;
}

class Quit : public ClientPacket {
public:
    Quit();
    Quit(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Quit BuildQuit() {
    Quit e;

    return e;
}

class GuildLeave : public ClientPacket {
public:
    GuildLeave();
    GuildLeave(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline GuildLeave BuildGuildLeave() {
    GuildLeave e;

    return e;
}

class RequestAccountState : public ClientPacket {
public:
    RequestAccountState();
    RequestAccountState(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RequestAccountState BuildRequestAccountState() {
    RequestAccountState e;

    return e;
}

class PetStand : public ClientPacket {
public:
    PetStand();
    PetStand(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline PetStand BuildPetStand() {
    PetStand e;

    return e;
}

class PetFollow : public ClientPacket {
public:
    PetFollow();
    PetFollow(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline PetFollow BuildPetFollow() {
    PetFollow e;

    return e;
}

class ReleasePet : public ClientPacket {
public:
    ReleasePet();
    ReleasePet(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ReleasePet BuildReleasePet() {
    ReleasePet e;

    return e;
}

class TrainList : public ClientPacket {
public:
    TrainList();
    TrainList(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline TrainList BuildTrainList() {
    TrainList e;

    return e;
}

class Rest : public ClientPacket {
public:
    Rest();
    Rest(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Rest BuildRest() {
    Rest e;

    return e;
}

class Meditate : public ClientPacket {
public:
    Meditate();
    Meditate(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Meditate BuildMeditate() {
    Meditate e;

    return e;
}

class Resucitate : public ClientPacket {
public:
    Resucitate();
    Resucitate(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Resucitate BuildResucitate() {
    Resucitate e;

    return e;
}

class Heal : public ClientPacket {
public:
    Heal();
    Heal(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Heal BuildHeal() {
    Heal e;

    return e;
}

class Help : public ClientPacket {
public:
    Help();
    Help(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Help BuildHelp() {
    Help e;

    return e;
}

class RequestStats : public ClientPacket {
public:
    RequestStats();
    RequestStats(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RequestStats BuildRequestStats() {
    RequestStats e;

    return e;
}

class CommerceStart : public ClientPacket {
public:
    CommerceStart();
    CommerceStart(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline CommerceStart BuildCommerceStart() {
    CommerceStart e;

    return e;
}

class BankStart : public ClientPacket {
public:
    BankStart();
    BankStart(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline BankStart BuildBankStart() {
    BankStart e;

    return e;
}

class Enlist : public ClientPacket {
public:
    Enlist();
    Enlist(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Enlist BuildEnlist() {
    Enlist e;

    return e;
}

class Information : public ClientPacket {
public:
    Information();
    Information(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Information BuildInformation() {
    Information e;

    return e;
}

class Reward : public ClientPacket {
public:
    Reward();
    Reward(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Reward BuildReward() {
    Reward e;

    return e;
}

class RequestMOTD : public ClientPacket {
public:
    RequestMOTD();
    RequestMOTD(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RequestMOTD BuildRequestMOTD() {
    RequestMOTD e;

    return e;
}

class UpTime : public ClientPacket {
public:
    UpTime();
    UpTime(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline UpTime BuildUpTime() {
    UpTime e;

    return e;
}

class PartyLeave : public ClientPacket {
public:
    PartyLeave();
    PartyLeave(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline PartyLeave BuildPartyLeave() {
    PartyLeave e;

    return e;
}

class PartyCreate : public ClientPacket {
public:
    PartyCreate();
    PartyCreate(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline PartyCreate BuildPartyCreate() {
    PartyCreate e;

    return e;
}

class PartyJoin : public ClientPacket {
public:
    PartyJoin();
    PartyJoin(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline PartyJoin BuildPartyJoin() {
    PartyJoin e;

    return e;
}

class Inquiry : public ClientPacket {
public:
    Inquiry();
    Inquiry(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Inquiry BuildInquiry() {
    Inquiry e;

    return e;
}

class GuildMessage : public ClientPacket {
public:
    GuildMessage();
    GuildMessage(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Chat; 
};

inline GuildMessage BuildGuildMessage(const std::string& Chat) {
    GuildMessage e;
        e.Chat = Chat;
    return e;
}

class PartyMessage : public ClientPacket {
public:
    PartyMessage();
    PartyMessage(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Chat; 
};

inline PartyMessage BuildPartyMessage(const std::string& Chat) {
    PartyMessage e;
        e.Chat = Chat;
    return e;
}

class CentinelReport : public ClientPacket {
public:
    CentinelReport();
    CentinelReport(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t Code; 
};

inline CentinelReport BuildCentinelReport(std::int16_t Code) {
    CentinelReport e;
        e.Code = Code;
    return e;
}

class GuildOnline : public ClientPacket {
public:
    GuildOnline();
    GuildOnline(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline GuildOnline BuildGuildOnline() {
    GuildOnline e;

    return e;
}

class PartyOnline : public ClientPacket {
public:
    PartyOnline();
    PartyOnline(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline PartyOnline BuildPartyOnline() {
    PartyOnline e;

    return e;
}

class CouncilMessage : public ClientPacket {
public:
    CouncilMessage();
    CouncilMessage(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Chat; 
};

inline CouncilMessage BuildCouncilMessage(const std::string& Chat) {
    CouncilMessage e;
        e.Chat = Chat;
    return e;
}

class RoleMasterRequest : public ClientPacket {
public:
    RoleMasterRequest();
    RoleMasterRequest(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Request; 
};

inline RoleMasterRequest BuildRoleMasterRequest(const std::string& Request) {
    RoleMasterRequest e;
        e.Request = Request;
    return e;
}

class GMRequest : public ClientPacket {
public:
    GMRequest();
    GMRequest(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline GMRequest BuildGMRequest() {
    GMRequest e;

    return e;
}

class BugReport : public ClientPacket {
public:
    BugReport();
    BugReport(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Report; 
};

inline BugReport BuildBugReport(const std::string& Report) {
    BugReport e;
        e.Report = Report;
    return e;
}

class ChangeDescription : public ClientPacket {
public:
    ChangeDescription();
    ChangeDescription(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Description; 
};

inline ChangeDescription BuildChangeDescription(const std::string& Description) {
    ChangeDescription e;
        e.Description = Description;
    return e;
}

class GuildVote : public ClientPacket {
public:
    GuildVote();
    GuildVote(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Vote; 
};

inline GuildVote BuildGuildVote(const std::string& Vote) {
    GuildVote e;
        e.Vote = Vote;
    return e;
}

class Punishments : public ClientPacket {
public:
    Punishments();
    Punishments(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Name; 
};

inline Punishments BuildPunishments(const std::string& Name) {
    Punishments e;
        e.Name = Name;
    return e;
}

class ChangePassword : public ClientPacket {
public:
    ChangePassword();
    ChangePassword(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string OldPass; 
    std::string NewPass; 
};

inline ChangePassword BuildChangePassword(const std::string& OldPass, const std::string& NewPass) {
    ChangePassword e;
        e.OldPass = OldPass;
        e.NewPass = NewPass;
    return e;
}

class Gamble : public ClientPacket {
public:
    Gamble();
    Gamble(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t Amount; 
};

inline Gamble BuildGamble(std::int16_t Amount) {
    Gamble e;
        e.Amount = Amount;
    return e;
}

class InquiryVote : public ClientPacket {
public:
    InquiryVote();
    InquiryVote(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Opt; 
};

inline InquiryVote BuildInquiryVote(std::uint8_t Opt) {
    InquiryVote e;
        e.Opt = Opt;
    return e;
}

class LeaveFaction : public ClientPacket {
public:
    LeaveFaction();
    LeaveFaction(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline LeaveFaction BuildLeaveFaction() {
    LeaveFaction e;

    return e;
}

class BankExtractGold : public ClientPacket {
public:
    BankExtractGold();
    BankExtractGold(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int32_t Amount; 
};

inline BankExtractGold BuildBankExtractGold(std::int32_t Amount) {
    BankExtractGold e;
        e.Amount = Amount;
    return e;
}

class BankDepositGold : public ClientPacket {
public:
    BankDepositGold();
    BankDepositGold(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int32_t Amount; 
};

inline BankDepositGold BuildBankDepositGold(std::int32_t Amount) {
    BankDepositGold e;
        e.Amount = Amount;
    return e;
}

class Denounce : public ClientPacket {
public:
    Denounce();
    Denounce(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Text; 
};

inline Denounce BuildDenounce(const std::string& Text) {
    Denounce e;
        e.Text = Text;
    return e;
}

class GuildFundate : public ClientPacket {
public:
    GuildFundate();
    GuildFundate(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline GuildFundate BuildGuildFundate() {
    GuildFundate e;

    return e;
}

class GuildFundation : public ClientPacket {
public:
    GuildFundation();
    GuildFundation(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t ClanType; 
};

inline GuildFundation BuildGuildFundation(std::uint8_t ClanType) {
    GuildFundation e;
        e.ClanType = ClanType;
    return e;
}

class PartyKick : public ClientPacket {
public:
    PartyKick();
    PartyKick(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline PartyKick BuildPartyKick(const std::string& UserName) {
    PartyKick e;
        e.UserName = UserName;
    return e;
}

class PartySetLeader : public ClientPacket {
public:
    PartySetLeader();
    PartySetLeader(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline PartySetLeader BuildPartySetLeader(const std::string& UserName) {
    PartySetLeader e;
        e.UserName = UserName;
    return e;
}

class PartyAcceptMember : public ClientPacket {
public:
    PartyAcceptMember();
    PartyAcceptMember(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline PartyAcceptMember BuildPartyAcceptMember(const std::string& UserName) {
    PartyAcceptMember e;
        e.UserName = UserName;
    return e;
}

class Ping : public ClientPacket {
public:
    Ping();
    Ping(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Ping BuildPing() {
    Ping e;

    return e;
}

class RequestPartyForm : public ClientPacket {
public:
    RequestPartyForm();
    RequestPartyForm(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RequestPartyForm BuildRequestPartyForm() {
    RequestPartyForm e;

    return e;
}

class ItemUpgrade : public ClientPacket {
public:
    ItemUpgrade();
    ItemUpgrade(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t ItemIndex; 
};

inline ItemUpgrade BuildItemUpgrade(std::int16_t ItemIndex) {
    ItemUpgrade e;
        e.ItemIndex = ItemIndex;
    return e;
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

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int32_t TotalItems; 
    std::int16_t ItemsPorCiclo; 
};

inline InitCrafting BuildInitCrafting(std::int32_t TotalItems, std::int16_t ItemsPorCiclo) {
    InitCrafting e;
        e.TotalItems = TotalItems;
        e.ItemsPorCiclo = ItemsPorCiclo;
    return e;
}

class Home : public ClientPacket {
public:
    Home();
    Home(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Home BuildHome() {
    Home e;

    return e;
}

class ShowGuildNews : public ClientPacket {
public:
    ShowGuildNews();
    ShowGuildNews(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ShowGuildNews BuildShowGuildNews() {
    ShowGuildNews e;

    return e;
}

class ShareNpc : public ClientPacket {
public:
    ShareNpc();
    ShareNpc(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ShareNpc BuildShareNpc() {
    ShareNpc e;

    return e;
}

class StopSharingNpc : public ClientPacket {
public:
    StopSharingNpc();
    StopSharingNpc(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline StopSharingNpc BuildStopSharingNpc() {
    StopSharingNpc e;

    return e;
}

class Consultation : public ClientPacket {
public:
    Consultation();
    Consultation(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Consultation BuildConsultation() {
    Consultation e;

    return e;
}

class MoveItem : public ClientPacket {
public:
    MoveItem();
    MoveItem(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t OldSlot; 
    std::uint8_t NewSlot; 
};

inline MoveItem BuildMoveItem(std::uint8_t OldSlot, std::uint8_t NewSlot) {
    MoveItem e;
        e.OldSlot = OldSlot;
        e.NewSlot = NewSlot;
    return e;
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

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Chat; 
};

inline GMMessage BuildGMMessage(const std::string& Chat) {
    GMMessage e;
        e.Chat = Chat;
    return e;
}

class ShowName : public ClientGMPacket {
public:
    ShowName();
    ShowName(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ShowName BuildShowName() {
    ShowName e;

    return e;
}

class OnlineRoyalArmy : public ClientGMPacket {
public:
    OnlineRoyalArmy();
    OnlineRoyalArmy(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline OnlineRoyalArmy BuildOnlineRoyalArmy() {
    OnlineRoyalArmy e;

    return e;
}

class OnlineChaosLegion : public ClientGMPacket {
public:
    OnlineChaosLegion();
    OnlineChaosLegion(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline OnlineChaosLegion BuildOnlineChaosLegion() {
    OnlineChaosLegion e;

    return e;
}

class GoNearby : public ClientGMPacket {
public:
    GoNearby();
    GoNearby(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline GoNearby BuildGoNearby(const std::string& UserName) {
    GoNearby e;
        e.UserName = UserName;
    return e;
}

class Comment : public ClientGMPacket {
public:
    Comment();
    Comment(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Data; 
};

inline Comment BuildComment(const std::string& Data) {
    Comment e;
        e.Data = Data;
    return e;
}

class ServerTime : public ClientGMPacket {
public:
    ServerTime();
    ServerTime(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ServerTime BuildServerTime() {
    ServerTime e;

    return e;
}

class Where : public ClientGMPacket {
public:
    Where();
    Where(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline Where BuildWhere(const std::string& UserName) {
    Where e;
        e.UserName = UserName;
    return e;
}

class CreaturesInMap : public ClientGMPacket {
public:
    CreaturesInMap();
    CreaturesInMap(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t Map; 
};

inline CreaturesInMap BuildCreaturesInMap(std::int16_t Map) {
    CreaturesInMap e;
        e.Map = Map;
    return e;
}

class WarpMeToTarget : public ClientGMPacket {
public:
    WarpMeToTarget();
    WarpMeToTarget(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline WarpMeToTarget BuildWarpMeToTarget() {
    WarpMeToTarget e;

    return e;
}

class WarpChar : public ClientGMPacket {
public:
    WarpChar();
    WarpChar(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::int16_t Map; 
    std::uint8_t X; 
    std::uint8_t Y; 
};

inline WarpChar BuildWarpChar(const std::string& UserName, std::int16_t Map, std::uint8_t X, std::uint8_t Y) {
    WarpChar e;
        e.UserName = UserName;
        e.Map = Map;
        e.X = X;
        e.Y = Y;
    return e;
}

class Silence : public ClientGMPacket {
public:
    Silence();
    Silence(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline Silence BuildSilence(const std::string& UserName) {
    Silence e;
        e.UserName = UserName;
    return e;
}

class SOSShowList : public ClientGMPacket {
public:
    SOSShowList();
    SOSShowList(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline SOSShowList BuildSOSShowList() {
    SOSShowList e;

    return e;
}

class SOSRemove : public ClientGMPacket {
public:
    SOSRemove();
    SOSRemove(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline SOSRemove BuildSOSRemove(const std::string& UserName) {
    SOSRemove e;
        e.UserName = UserName;
    return e;
}

class GoToChar : public ClientGMPacket {
public:
    GoToChar();
    GoToChar(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline GoToChar BuildGoToChar(const std::string& UserName) {
    GoToChar e;
        e.UserName = UserName;
    return e;
}

class Invisible : public ClientGMPacket {
public:
    Invisible();
    Invisible(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Invisible BuildInvisible() {
    Invisible e;

    return e;
}

class GMPanel : public ClientGMPacket {
public:
    GMPanel();
    GMPanel(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline GMPanel BuildGMPanel() {
    GMPanel e;

    return e;
}

class RequestUserList : public ClientGMPacket {
public:
    RequestUserList();
    RequestUserList(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RequestUserList BuildRequestUserList() {
    RequestUserList e;

    return e;
}

class Working : public ClientGMPacket {
public:
    Working();
    Working(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Working BuildWorking() {
    Working e;

    return e;
}

class Hiding : public ClientGMPacket {
public:
    Hiding();
    Hiding(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Hiding BuildHiding() {
    Hiding e;

    return e;
}

class Jail : public ClientGMPacket {
public:
    Jail();
    Jail(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::string Reason; 
    std::uint8_t JailTime; 
};

inline Jail BuildJail(const std::string& UserName, const std::string& Reason, std::uint8_t JailTime) {
    Jail e;
        e.UserName = UserName;
        e.Reason = Reason;
        e.JailTime = JailTime;
    return e;
}

class KillNPC : public ClientGMPacket {
public:
    KillNPC();
    KillNPC(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline KillNPC BuildKillNPC() {
    KillNPC e;

    return e;
}

class WarnUser : public ClientGMPacket {
public:
    WarnUser();
    WarnUser(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::string Reason; 
};

inline WarnUser BuildWarnUser(const std::string& UserName, const std::string& Reason) {
    WarnUser e;
        e.UserName = UserName;
        e.Reason = Reason;
    return e;
}

class EditChar : public ClientGMPacket {
public:
    EditChar();
    EditChar(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::uint8_t Opcion; 
    std::string Arg1; 
    std::string Arg2; 
};

inline EditChar BuildEditChar(const std::string& UserName, std::uint8_t Opcion, const std::string& Arg1, const std::string& Arg2) {
    EditChar e;
        e.UserName = UserName;
        e.Opcion = Opcion;
        e.Arg1 = Arg1;
        e.Arg2 = Arg2;
    return e;
}

class RequestCharInfo : public ClientGMPacket {
public:
    RequestCharInfo();
    RequestCharInfo(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string TargetName; 
};

inline RequestCharInfo BuildRequestCharInfo(const std::string& TargetName) {
    RequestCharInfo e;
        e.TargetName = TargetName;
    return e;
}

class RequestCharStats : public ClientGMPacket {
public:
    RequestCharStats();
    RequestCharStats(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline RequestCharStats BuildRequestCharStats(const std::string& UserName) {
    RequestCharStats e;
        e.UserName = UserName;
    return e;
}

class RequestCharGold : public ClientGMPacket {
public:
    RequestCharGold();
    RequestCharGold(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline RequestCharGold BuildRequestCharGold(const std::string& UserName) {
    RequestCharGold e;
        e.UserName = UserName;
    return e;
}

class RequestCharInventory : public ClientGMPacket {
public:
    RequestCharInventory();
    RequestCharInventory(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline RequestCharInventory BuildRequestCharInventory(const std::string& UserName) {
    RequestCharInventory e;
        e.UserName = UserName;
    return e;
}

class RequestCharBank : public ClientGMPacket {
public:
    RequestCharBank();
    RequestCharBank(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline RequestCharBank BuildRequestCharBank(const std::string& UserName) {
    RequestCharBank e;
        e.UserName = UserName;
    return e;
}

class RequestCharSkills : public ClientGMPacket {
public:
    RequestCharSkills();
    RequestCharSkills(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline RequestCharSkills BuildRequestCharSkills(const std::string& UserName) {
    RequestCharSkills e;
        e.UserName = UserName;
    return e;
}

class ReviveChar : public ClientGMPacket {
public:
    ReviveChar();
    ReviveChar(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline ReviveChar BuildReviveChar(const std::string& UserName) {
    ReviveChar e;
        e.UserName = UserName;
    return e;
}

class OnlineGM : public ClientGMPacket {
public:
    OnlineGM();
    OnlineGM(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline OnlineGM BuildOnlineGM() {
    OnlineGM e;

    return e;
}

class OnlineMap : public ClientGMPacket {
public:
    OnlineMap();
    OnlineMap(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t Map; 
};

inline OnlineMap BuildOnlineMap(std::int16_t Map) {
    OnlineMap e;
        e.Map = Map;
    return e;
}

class Forgive : public ClientGMPacket {
public:
    Forgive();
    Forgive(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline Forgive BuildForgive(const std::string& UserName) {
    Forgive e;
        e.UserName = UserName;
    return e;
}

class Kick : public ClientGMPacket {
public:
    Kick();
    Kick(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline Kick BuildKick(const std::string& UserName) {
    Kick e;
        e.UserName = UserName;
    return e;
}

class Execute : public ClientGMPacket {
public:
    Execute();
    Execute(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline Execute BuildExecute(const std::string& UserName) {
    Execute e;
        e.UserName = UserName;
    return e;
}

class BanChar : public ClientGMPacket {
public:
    BanChar();
    BanChar(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::string Reason; 
};

inline BanChar BuildBanChar(const std::string& UserName, const std::string& Reason) {
    BanChar e;
        e.UserName = UserName;
        e.Reason = Reason;
    return e;
}

class UnbanChar : public ClientGMPacket {
public:
    UnbanChar();
    UnbanChar(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline UnbanChar BuildUnbanChar(const std::string& UserName) {
    UnbanChar e;
        e.UserName = UserName;
    return e;
}

class NPCFollow : public ClientGMPacket {
public:
    NPCFollow();
    NPCFollow(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline NPCFollow BuildNPCFollow() {
    NPCFollow e;

    return e;
}

class SummonChar : public ClientGMPacket {
public:
    SummonChar();
    SummonChar(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline SummonChar BuildSummonChar(const std::string& UserName) {
    SummonChar e;
        e.UserName = UserName;
    return e;
}

class SpawnListRequest : public ClientGMPacket {
public:
    SpawnListRequest();
    SpawnListRequest(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline SpawnListRequest BuildSpawnListRequest() {
    SpawnListRequest e;

    return e;
}

class SpawnCreature : public ClientGMPacket {
public:
    SpawnCreature();
    SpawnCreature(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t NPC; 
};

inline SpawnCreature BuildSpawnCreature(std::int16_t NPC) {
    SpawnCreature e;
        e.NPC = NPC;
    return e;
}

class ResetNPCInventory : public ClientGMPacket {
public:
    ResetNPCInventory();
    ResetNPCInventory(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ResetNPCInventory BuildResetNPCInventory() {
    ResetNPCInventory e;

    return e;
}

class CleanWorld : public ClientGMPacket {
public:
    CleanWorld();
    CleanWorld(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline CleanWorld BuildCleanWorld() {
    CleanWorld e;

    return e;
}

class ServerMessage : public ClientGMPacket {
public:
    ServerMessage();
    ServerMessage(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Message; 
};

inline ServerMessage BuildServerMessage(const std::string& Message) {
    ServerMessage e;
        e.Message = Message;
    return e;
}

class NickToIP : public ClientGMPacket {
public:
    NickToIP();
    NickToIP(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline NickToIP BuildNickToIP(const std::string& UserName) {
    NickToIP e;
        e.UserName = UserName;
    return e;
}

class IPToNick : public ClientGMPacket {
public:
    IPToNick();
    IPToNick(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t A; 
    std::uint8_t B; 
    std::uint8_t C; 
    std::uint8_t D; 
};

inline IPToNick BuildIPToNick(std::uint8_t A, std::uint8_t B, std::uint8_t C, std::uint8_t D) {
    IPToNick e;
        e.A = A;
        e.B = B;
        e.C = C;
        e.D = D;
    return e;
}

class GuildOnlineMembers : public ClientGMPacket {
public:
    GuildOnlineMembers();
    GuildOnlineMembers(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string GuildName; 
};

inline GuildOnlineMembers BuildGuildOnlineMembers(const std::string& GuildName) {
    GuildOnlineMembers e;
        e.GuildName = GuildName;
    return e;
}

class TeleportCreate : public ClientGMPacket {
public:
    TeleportCreate();
    TeleportCreate(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t Map; 
    std::uint8_t X; 
    std::uint8_t Y; 
    std::uint8_t Radio; 
};

inline TeleportCreate BuildTeleportCreate(std::int16_t Map, std::uint8_t X, std::uint8_t Y, std::uint8_t Radio) {
    TeleportCreate e;
        e.Map = Map;
        e.X = X;
        e.Y = Y;
        e.Radio = Radio;
    return e;
}

class TeleportDestroy : public ClientGMPacket {
public:
    TeleportDestroy();
    TeleportDestroy(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline TeleportDestroy BuildTeleportDestroy() {
    TeleportDestroy e;

    return e;
}

class RainToggle : public ClientGMPacket {
public:
    RainToggle();
    RainToggle(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RainToggle BuildRainToggle() {
    RainToggle e;

    return e;
}

class SetCharDescription : public ClientGMPacket {
public:
    SetCharDescription();
    SetCharDescription(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Description; 
};

inline SetCharDescription BuildSetCharDescription(const std::string& Description) {
    SetCharDescription e;
        e.Description = Description;
    return e;
}

class ForceMIDIToMap : public ClientGMPacket {
public:
    ForceMIDIToMap();
    ForceMIDIToMap(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t MidiID; 
    std::int16_t Map; 
};

inline ForceMIDIToMap BuildForceMIDIToMap(std::uint8_t MidiID, std::int16_t Map) {
    ForceMIDIToMap e;
        e.MidiID = MidiID;
        e.Map = Map;
    return e;
}

class ForceWAVEToMap : public ClientGMPacket {
public:
    ForceWAVEToMap();
    ForceWAVEToMap(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Wave; 
    std::int16_t Map; 
    std::uint8_t X; 
    std::uint8_t Y; 
};

inline ForceWAVEToMap BuildForceWAVEToMap(std::uint8_t Wave, std::int16_t Map, std::uint8_t X, std::uint8_t Y) {
    ForceWAVEToMap e;
        e.Wave = Wave;
        e.Map = Map;
        e.X = X;
        e.Y = Y;
    return e;
}

class RoyalArmyMessage : public ClientGMPacket {
public:
    RoyalArmyMessage();
    RoyalArmyMessage(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Message; 
};

inline RoyalArmyMessage BuildRoyalArmyMessage(const std::string& Message) {
    RoyalArmyMessage e;
        e.Message = Message;
    return e;
}

class ChaosLegionMessage : public ClientGMPacket {
public:
    ChaosLegionMessage();
    ChaosLegionMessage(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Message; 
};

inline ChaosLegionMessage BuildChaosLegionMessage(const std::string& Message) {
    ChaosLegionMessage e;
        e.Message = Message;
    return e;
}

class CitizenMessage : public ClientGMPacket {
public:
    CitizenMessage();
    CitizenMessage(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Message; 
};

inline CitizenMessage BuildCitizenMessage(const std::string& Message) {
    CitizenMessage e;
        e.Message = Message;
    return e;
}

class CriminalMessage : public ClientGMPacket {
public:
    CriminalMessage();
    CriminalMessage(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Message; 
};

inline CriminalMessage BuildCriminalMessage(const std::string& Message) {
    CriminalMessage e;
        e.Message = Message;
    return e;
}

class TalkAsNPC : public ClientGMPacket {
public:
    TalkAsNPC();
    TalkAsNPC(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Message; 
};

inline TalkAsNPC BuildTalkAsNPC(const std::string& Message) {
    TalkAsNPC e;
        e.Message = Message;
    return e;
}

class DestroyAllItemsInArea : public ClientGMPacket {
public:
    DestroyAllItemsInArea();
    DestroyAllItemsInArea(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline DestroyAllItemsInArea BuildDestroyAllItemsInArea() {
    DestroyAllItemsInArea e;

    return e;
}

class AcceptRoyalCouncilMember : public ClientGMPacket {
public:
    AcceptRoyalCouncilMember();
    AcceptRoyalCouncilMember(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline AcceptRoyalCouncilMember BuildAcceptRoyalCouncilMember(const std::string& UserName) {
    AcceptRoyalCouncilMember e;
        e.UserName = UserName;
    return e;
}

class AcceptChaosCouncilMember : public ClientGMPacket {
public:
    AcceptChaosCouncilMember();
    AcceptChaosCouncilMember(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline AcceptChaosCouncilMember BuildAcceptChaosCouncilMember(const std::string& UserName) {
    AcceptChaosCouncilMember e;
        e.UserName = UserName;
    return e;
}

class ItemsInTheFloor : public ClientGMPacket {
public:
    ItemsInTheFloor();
    ItemsInTheFloor(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ItemsInTheFloor BuildItemsInTheFloor() {
    ItemsInTheFloor e;

    return e;
}

class MakeDumb : public ClientGMPacket {
public:
    MakeDumb();
    MakeDumb(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline MakeDumb BuildMakeDumb(const std::string& UserName) {
    MakeDumb e;
        e.UserName = UserName;
    return e;
}

class MakeDumbNoMore : public ClientGMPacket {
public:
    MakeDumbNoMore();
    MakeDumbNoMore(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline MakeDumbNoMore BuildMakeDumbNoMore(const std::string& UserName) {
    MakeDumbNoMore e;
        e.UserName = UserName;
    return e;
}

class DumpIPTables : public ClientGMPacket {
public:
    DumpIPTables();
    DumpIPTables(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline DumpIPTables BuildDumpIPTables() {
    DumpIPTables e;

    return e;
}

class CouncilKick : public ClientGMPacket {
public:
    CouncilKick();
    CouncilKick(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline CouncilKick BuildCouncilKick(const std::string& UserName) {
    CouncilKick e;
        e.UserName = UserName;
    return e;
}

class SetTrigger : public ClientGMPacket {
public:
    SetTrigger();
    SetTrigger(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Trigger; 
};

inline SetTrigger BuildSetTrigger(std::uint8_t Trigger) {
    SetTrigger e;
        e.Trigger = Trigger;
    return e;
}

class AskTrigger : public ClientGMPacket {
public:
    AskTrigger();
    AskTrigger(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline AskTrigger BuildAskTrigger() {
    AskTrigger e;

    return e;
}

class BannedIPList : public ClientGMPacket {
public:
    BannedIPList();
    BannedIPList(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline BannedIPList BuildBannedIPList() {
    BannedIPList e;

    return e;
}

class BannedIPReload : public ClientGMPacket {
public:
    BannedIPReload();
    BannedIPReload(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline BannedIPReload BuildBannedIPReload() {
    BannedIPReload e;

    return e;
}

class GuildMemberList : public ClientGMPacket {
public:
    GuildMemberList();
    GuildMemberList(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string GuildName; 
};

inline GuildMemberList BuildGuildMemberList(const std::string& GuildName) {
    GuildMemberList e;
        e.GuildName = GuildName;
    return e;
}

class GuildBan : public ClientGMPacket {
public:
    GuildBan();
    GuildBan(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string GuildName; 
};

inline GuildBan BuildGuildBan(const std::string& GuildName) {
    GuildBan e;
        e.GuildName = GuildName;
    return e;
}

class BanIP : public ClientGMPacket {
public:
    BanIP();
    BanIP(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string IP; 
    std::string Reason; 
};

inline BanIP BuildBanIP(const std::string& IP, const std::string& Reason) {
    BanIP e;
        e.IP = IP;
        e.Reason = Reason;
    return e;
}

class UnbanIP : public ClientGMPacket {
public:
    UnbanIP();
    UnbanIP(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string IP; 
};

inline UnbanIP BuildUnbanIP(const std::string& IP) {
    UnbanIP e;
        e.IP = IP;
    return e;
}

class CreateItem : public ClientGMPacket {
public:
    CreateItem();
    CreateItem(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t Item; 
};

inline CreateItem BuildCreateItem(std::int16_t Item) {
    CreateItem e;
        e.Item = Item;
    return e;
}

class DestroyItems : public ClientGMPacket {
public:
    DestroyItems();
    DestroyItems(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline DestroyItems BuildDestroyItems() {
    DestroyItems e;

    return e;
}

class ChaosLegionKick : public ClientGMPacket {
public:
    ChaosLegionKick();
    ChaosLegionKick(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::string Reason; 
};

inline ChaosLegionKick BuildChaosLegionKick(const std::string& UserName, const std::string& Reason) {
    ChaosLegionKick e;
        e.UserName = UserName;
        e.Reason = Reason;
    return e;
}

class RoyalArmyKick : public ClientGMPacket {
public:
    RoyalArmyKick();
    RoyalArmyKick(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::string Reason; 
};

inline RoyalArmyKick BuildRoyalArmyKick(const std::string& UserName, const std::string& Reason) {
    RoyalArmyKick e;
        e.UserName = UserName;
        e.Reason = Reason;
    return e;
}

class ForceMIDIAll : public ClientGMPacket {
public:
    ForceMIDIAll();
    ForceMIDIAll(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t MidiID; 
};

inline ForceMIDIAll BuildForceMIDIAll(std::uint8_t MidiID) {
    ForceMIDIAll e;
        e.MidiID = MidiID;
    return e;
}

class ForceWAVEAll : public ClientGMPacket {
public:
    ForceWAVEAll();
    ForceWAVEAll(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t WaveID; 
};

inline ForceWAVEAll BuildForceWAVEAll(std::uint8_t WaveID) {
    ForceWAVEAll e;
        e.WaveID = WaveID;
    return e;
}

class RemovePunishment : public ClientGMPacket {
public:
    RemovePunishment();
    RemovePunishment(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::uint8_t Punishment; 
    std::string NewText; 
};

inline RemovePunishment BuildRemovePunishment(const std::string& UserName, std::uint8_t Punishment, const std::string& NewText) {
    RemovePunishment e;
        e.UserName = UserName;
        e.Punishment = Punishment;
        e.NewText = NewText;
    return e;
}

class TileBlockedToggle : public ClientGMPacket {
public:
    TileBlockedToggle();
    TileBlockedToggle(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline TileBlockedToggle BuildTileBlockedToggle() {
    TileBlockedToggle e;

    return e;
}

class KillNPCNoRespawn : public ClientGMPacket {
public:
    KillNPCNoRespawn();
    KillNPCNoRespawn(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline KillNPCNoRespawn BuildKillNPCNoRespawn() {
    KillNPCNoRespawn e;

    return e;
}

class KillAllNearbyNPCs : public ClientGMPacket {
public:
    KillAllNearbyNPCs();
    KillAllNearbyNPCs(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline KillAllNearbyNPCs BuildKillAllNearbyNPCs() {
    KillAllNearbyNPCs e;

    return e;
}

class LastIP : public ClientGMPacket {
public:
    LastIP();
    LastIP(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline LastIP BuildLastIP(const std::string& UserName) {
    LastIP e;
        e.UserName = UserName;
    return e;
}

class ChangeMOTD : public ClientGMPacket {
public:
    ChangeMOTD();
    ChangeMOTD(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ChangeMOTD BuildChangeMOTD() {
    ChangeMOTD e;

    return e;
}

class SetMOTD : public ClientGMPacket {
public:
    SetMOTD();
    SetMOTD(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Motd; 
};

inline SetMOTD BuildSetMOTD(const std::string& Motd) {
    SetMOTD e;
        e.Motd = Motd;
    return e;
}

class SystemMessage : public ClientGMPacket {
public:
    SystemMessage();
    SystemMessage(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Message; 
};

inline SystemMessage BuildSystemMessage(const std::string& Message) {
    SystemMessage e;
        e.Message = Message;
    return e;
}

class CreateNPC : public ClientGMPacket {
public:
    CreateNPC();
    CreateNPC(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t NpcIndex; 
};

inline CreateNPC BuildCreateNPC(std::int16_t NpcIndex) {
    CreateNPC e;
        e.NpcIndex = NpcIndex;
    return e;
}

class CreateNPCWithRespawn : public ClientGMPacket {
public:
    CreateNPCWithRespawn();
    CreateNPCWithRespawn(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t NpcIndex; 
};

inline CreateNPCWithRespawn BuildCreateNPCWithRespawn(std::int16_t NpcIndex) {
    CreateNPCWithRespawn e;
        e.NpcIndex = NpcIndex;
    return e;
}

class ImperialArmour : public ClientGMPacket {
public:
    ImperialArmour();
    ImperialArmour(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Index; 
    std::int16_t ObjIndex; 
};

inline ImperialArmour BuildImperialArmour(std::uint8_t Index, std::int16_t ObjIndex) {
    ImperialArmour e;
        e.Index = Index;
        e.ObjIndex = ObjIndex;
    return e;
}

class ChaosArmour : public ClientGMPacket {
public:
    ChaosArmour();
    ChaosArmour(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Index; 
    std::int16_t ObjIndex; 
};

inline ChaosArmour BuildChaosArmour(std::uint8_t Index, std::int16_t ObjIndex) {
    ChaosArmour e;
        e.Index = Index;
        e.ObjIndex = ObjIndex;
    return e;
}

class NavigateToggle : public ClientGMPacket {
public:
    NavigateToggle();
    NavigateToggle(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline NavigateToggle BuildNavigateToggle() {
    NavigateToggle e;

    return e;
}

class ServerOpenToUsersToggle : public ClientGMPacket {
public:
    ServerOpenToUsersToggle();
    ServerOpenToUsersToggle(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ServerOpenToUsersToggle BuildServerOpenToUsersToggle() {
    ServerOpenToUsersToggle e;

    return e;
}

class TurnOffServer : public ClientGMPacket {
public:
    TurnOffServer();
    TurnOffServer(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline TurnOffServer BuildTurnOffServer() {
    TurnOffServer e;

    return e;
}

class TurnCriminal : public ClientGMPacket {
public:
    TurnCriminal();
    TurnCriminal(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline TurnCriminal BuildTurnCriminal(const std::string& UserName) {
    TurnCriminal e;
        e.UserName = UserName;
    return e;
}

class ResetFactions : public ClientGMPacket {
public:
    ResetFactions();
    ResetFactions(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline ResetFactions BuildResetFactions(const std::string& UserName) {
    ResetFactions e;
        e.UserName = UserName;
    return e;
}

class RemoveCharFromGuild : public ClientGMPacket {
public:
    RemoveCharFromGuild();
    RemoveCharFromGuild(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline RemoveCharFromGuild BuildRemoveCharFromGuild(const std::string& UserName) {
    RemoveCharFromGuild e;
        e.UserName = UserName;
    return e;
}

class RequestCharMail : public ClientGMPacket {
public:
    RequestCharMail();
    RequestCharMail(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
};

inline RequestCharMail BuildRequestCharMail(const std::string& UserName) {
    RequestCharMail e;
        e.UserName = UserName;
    return e;
}

class AlterPassword : public ClientGMPacket {
public:
    AlterPassword();
    AlterPassword(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::string CopyFrom; 
};

inline AlterPassword BuildAlterPassword(const std::string& UserName, const std::string& CopyFrom) {
    AlterPassword e;
        e.UserName = UserName;
        e.CopyFrom = CopyFrom;
    return e;
}

class AlterMail : public ClientGMPacket {
public:
    AlterMail();
    AlterMail(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::string NewMail; 
};

inline AlterMail BuildAlterMail(const std::string& UserName, const std::string& NewMail) {
    AlterMail e;
        e.UserName = UserName;
        e.NewMail = NewMail;
    return e;
}

class AlterName : public ClientGMPacket {
public:
    AlterName();
    AlterName(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::string NewName; 
};

inline AlterName BuildAlterName(const std::string& UserName, const std::string& NewName) {
    AlterName e;
        e.UserName = UserName;
        e.NewName = NewName;
    return e;
}

class ToggleCentinelActivated : public ClientGMPacket {
public:
    ToggleCentinelActivated();
    ToggleCentinelActivated(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ToggleCentinelActivated BuildToggleCentinelActivated() {
    ToggleCentinelActivated e;

    return e;
}

class DoBackUp : public ClientGMPacket {
public:
    DoBackUp();
    DoBackUp(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline DoBackUp BuildDoBackUp() {
    DoBackUp e;

    return e;
}

class ShowGuildMessages : public ClientGMPacket {
public:
    ShowGuildMessages();
    ShowGuildMessages(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string GuildName; 
};

inline ShowGuildMessages BuildShowGuildMessages(const std::string& GuildName) {
    ShowGuildMessages e;
        e.GuildName = GuildName;
    return e;
}

class SaveMap : public ClientGMPacket {
public:
    SaveMap();
    SaveMap(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline SaveMap BuildSaveMap() {
    SaveMap e;

    return e;
}

class ChangeMapInfoPK : public ClientGMPacket {
public:
    ChangeMapInfoPK();
    ChangeMapInfoPK(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    bool Pk; 
};

inline ChangeMapInfoPK BuildChangeMapInfoPK(bool Pk) {
    ChangeMapInfoPK e;
        e.Pk = Pk;
    return e;
}

class ChangeMapInfoBackup : public ClientGMPacket {
public:
    ChangeMapInfoBackup();
    ChangeMapInfoBackup(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    bool Backup; 
};

inline ChangeMapInfoBackup BuildChangeMapInfoBackup(bool Backup) {
    ChangeMapInfoBackup e;
        e.Backup = Backup;
    return e;
}

class ChangeMapInfoRestricted : public ClientGMPacket {
public:
    ChangeMapInfoRestricted();
    ChangeMapInfoRestricted(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string RestrictedTo; 
};

inline ChangeMapInfoRestricted BuildChangeMapInfoRestricted(const std::string& RestrictedTo) {
    ChangeMapInfoRestricted e;
        e.RestrictedTo = RestrictedTo;
    return e;
}

class ChangeMapInfoNoMagic : public ClientGMPacket {
public:
    ChangeMapInfoNoMagic();
    ChangeMapInfoNoMagic(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    bool NoMagic; 
};

inline ChangeMapInfoNoMagic BuildChangeMapInfoNoMagic(bool NoMagic) {
    ChangeMapInfoNoMagic e;
        e.NoMagic = NoMagic;
    return e;
}

class ChangeMapInfoNoInvi : public ClientGMPacket {
public:
    ChangeMapInfoNoInvi();
    ChangeMapInfoNoInvi(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    bool NoInvi; 
};

inline ChangeMapInfoNoInvi BuildChangeMapInfoNoInvi(bool NoInvi) {
    ChangeMapInfoNoInvi e;
        e.NoInvi = NoInvi;
    return e;
}

class ChangeMapInfoNoResu : public ClientGMPacket {
public:
    ChangeMapInfoNoResu();
    ChangeMapInfoNoResu(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    bool NoResu; 
};

inline ChangeMapInfoNoResu BuildChangeMapInfoNoResu(bool NoResu) {
    ChangeMapInfoNoResu e;
        e.NoResu = NoResu;
    return e;
}

class ChangeMapInfoLand : public ClientGMPacket {
public:
    ChangeMapInfoLand();
    ChangeMapInfoLand(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Data; 
};

inline ChangeMapInfoLand BuildChangeMapInfoLand(const std::string& Data) {
    ChangeMapInfoLand e;
        e.Data = Data;
    return e;
}

class ChangeMapInfoZone : public ClientGMPacket {
public:
    ChangeMapInfoZone();
    ChangeMapInfoZone(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Data; 
};

inline ChangeMapInfoZone BuildChangeMapInfoZone(const std::string& Data) {
    ChangeMapInfoZone e;
        e.Data = Data;
    return e;
}

class ChangeMapInfoStealNpc : public ClientGMPacket {
public:
    ChangeMapInfoStealNpc();
    ChangeMapInfoStealNpc(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    bool RoboNpc; 
};

inline ChangeMapInfoStealNpc BuildChangeMapInfoStealNpc(bool RoboNpc) {
    ChangeMapInfoStealNpc e;
        e.RoboNpc = RoboNpc;
    return e;
}

class ChangeMapInfoNoOcultar : public ClientGMPacket {
public:
    ChangeMapInfoNoOcultar();
    ChangeMapInfoNoOcultar(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    bool NoOcultar; 
};

inline ChangeMapInfoNoOcultar BuildChangeMapInfoNoOcultar(bool NoOcultar) {
    ChangeMapInfoNoOcultar e;
        e.NoOcultar = NoOcultar;
    return e;
}

class ChangeMapInfoNoInvocar : public ClientGMPacket {
public:
    ChangeMapInfoNoInvocar();
    ChangeMapInfoNoInvocar(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    bool NoInvocar; 
};

inline ChangeMapInfoNoInvocar BuildChangeMapInfoNoInvocar(bool NoInvocar) {
    ChangeMapInfoNoInvocar e;
        e.NoInvocar = NoInvocar;
    return e;
}

class SaveChars : public ClientGMPacket {
public:
    SaveChars();
    SaveChars(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline SaveChars BuildSaveChars() {
    SaveChars e;

    return e;
}

class CleanSOS : public ClientGMPacket {
public:
    CleanSOS();
    CleanSOS(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline CleanSOS BuildCleanSOS() {
    CleanSOS e;

    return e;
}

class ShowServerForm : public ClientGMPacket {
public:
    ShowServerForm();
    ShowServerForm(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ShowServerForm BuildShowServerForm() {
    ShowServerForm e;

    return e;
}

class Night : public ClientGMPacket {
public:
    Night();
    Night(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Night BuildNight() {
    Night e;

    return e;
}

class KickAllChars : public ClientGMPacket {
public:
    KickAllChars();
    KickAllChars(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline KickAllChars BuildKickAllChars() {
    KickAllChars e;

    return e;
}

class ReloadNPCs : public ClientGMPacket {
public:
    ReloadNPCs();
    ReloadNPCs(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ReloadNPCs BuildReloadNPCs() {
    ReloadNPCs e;

    return e;
}

class ReloadServerIni : public ClientGMPacket {
public:
    ReloadServerIni();
    ReloadServerIni(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ReloadServerIni BuildReloadServerIni() {
    ReloadServerIni e;

    return e;
}

class ReloadSpells : public ClientGMPacket {
public:
    ReloadSpells();
    ReloadSpells(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ReloadSpells BuildReloadSpells() {
    ReloadSpells e;

    return e;
}

class ReloadObjects : public ClientGMPacket {
public:
    ReloadObjects();
    ReloadObjects(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ReloadObjects BuildReloadObjects() {
    ReloadObjects e;

    return e;
}

class Restart : public ClientGMPacket {
public:
    Restart();
    Restart(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Restart BuildRestart() {
    Restart e;

    return e;
}

class ResetAutoUpdate : public ClientGMPacket {
public:
    ResetAutoUpdate();
    ResetAutoUpdate(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ResetAutoUpdate BuildResetAutoUpdate() {
    ResetAutoUpdate e;

    return e;
}

class ChatColor : public ClientGMPacket {
public:
    ChatColor();
    ChatColor(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t R; 
    std::uint8_t G; 
    std::uint8_t B; 
};

inline ChatColor BuildChatColor(std::uint8_t R, std::uint8_t G, std::uint8_t B) {
    ChatColor e;
        e.R = R;
        e.G = G;
        e.B = B;
    return e;
}

class Ignored : public ClientGMPacket {
public:
    Ignored();
    Ignored(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Ignored BuildIgnored() {
    Ignored e;

    return e;
}

class CheckSlot : public ClientGMPacket {
public:
    CheckSlot();
    CheckSlot(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::uint8_t Slot; 
};

inline CheckSlot BuildCheckSlot(const std::string& UserName, std::uint8_t Slot) {
    CheckSlot e;
        e.UserName = UserName;
        e.Slot = Slot;
    return e;
}

class SetIniVar : public ClientGMPacket {
public:
    SetIniVar();
    SetIniVar(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Seccion; 
    std::string Clave; 
    std::string Valor; 
};

inline SetIniVar BuildSetIniVar(const std::string& Seccion, const std::string& Clave, const std::string& Valor) {
    SetIniVar e;
        e.Seccion = Seccion;
        e.Clave = Clave;
        e.Valor = Valor;
    return e;
}

class CreatePretorianClan : public ClientGMPacket {
public:
    CreatePretorianClan();
    CreatePretorianClan(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t Map; 
    std::uint8_t X; 
    std::uint8_t Y; 
};

inline CreatePretorianClan BuildCreatePretorianClan(std::int16_t Map, std::uint8_t X, std::uint8_t Y) {
    CreatePretorianClan e;
        e.Map = Map;
        e.X = X;
        e.Y = Y;
    return e;
}

class RemovePretorianClan : public ClientGMPacket {
public:
    RemovePretorianClan();
    RemovePretorianClan(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t Map; 
};

inline RemovePretorianClan BuildRemovePretorianClan(std::int16_t Map) {
    RemovePretorianClan e;
        e.Map = Map;
    return e;
}

class EnableDenounces : public ClientGMPacket {
public:
    EnableDenounces();
    EnableDenounces(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline EnableDenounces BuildEnableDenounces() {
    EnableDenounces e;

    return e;
}

class ShowDenouncesList : public ClientGMPacket {
public:
    ShowDenouncesList();
    ShowDenouncesList(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ShowDenouncesList BuildShowDenouncesList() {
    ShowDenouncesList e;

    return e;
}

class MapMessage : public ClientGMPacket {
public:
    MapMessage();
    MapMessage(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Message; 
};

inline MapMessage BuildMapMessage(const std::string& Message) {
    MapMessage e;
        e.Message = Message;
    return e;
}

class SetDialog : public ClientGMPacket {
public:
    SetDialog();
    SetDialog(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Message; 
};

inline SetDialog BuildSetDialog(const std::string& Message) {
    SetDialog e;
        e.Message = Message;
    return e;
}

class Impersonate : public ClientGMPacket {
public:
    Impersonate();
    Impersonate(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Impersonate BuildImpersonate() {
    Impersonate e;

    return e;
}

class Imitate : public ClientGMPacket {
public:
    Imitate();
    Imitate(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Imitate BuildImitate() {
    Imitate e;

    return e;
}

class RecordAdd : public ClientGMPacket {
public:
    RecordAdd();
    RecordAdd(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string UserName; 
    std::string Reason; 
};

inline RecordAdd BuildRecordAdd(const std::string& UserName, const std::string& Reason) {
    RecordAdd e;
        e.UserName = UserName;
        e.Reason = Reason;
    return e;
}

class RecordRemove : public ClientGMPacket {
public:
    RecordRemove();
    RecordRemove(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Index; 
};

inline RecordRemove BuildRecordRemove(std::uint8_t Index) {
    RecordRemove e;
        e.Index = Index;
    return e;
}

class RecordAddObs : public ClientGMPacket {
public:
    RecordAddObs();
    RecordAddObs(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Index; 
    std::string Obs; 
};

inline RecordAddObs BuildRecordAddObs(std::uint8_t Index, const std::string& Obs) {
    RecordAddObs e;
        e.Index = Index;
        e.Obs = Obs;
    return e;
}

class RecordListRequest : public ClientGMPacket {
public:
    RecordListRequest();
    RecordListRequest(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RecordListRequest BuildRecordListRequest() {
    RecordListRequest e;

    return e;
}

class RecordDetailsRequest : public ClientGMPacket {
public:
    RecordDetailsRequest();
    RecordDetailsRequest(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Index; 
};

inline RecordDetailsRequest BuildRecordDetailsRequest(std::uint8_t Index) {
    RecordDetailsRequest e;
        e.Index = Index;
    return e;
}

class AlterGuildName : public ClientGMPacket {
public:
    AlterGuildName();
    AlterGuildName(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string OldGuildName; 
    std::string NewGuildName; 
};

inline AlterGuildName BuildAlterGuildName(const std::string& OldGuildName, const std::string& NewGuildName) {
    AlterGuildName e;
        e.OldGuildName = OldGuildName;
        e.NewGuildName = NewGuildName;
    return e;
}

class HigherAdminsMessage : public ClientGMPacket {
public:
    HigherAdminsMessage();
    HigherAdminsMessage(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Message; 
};

inline HigherAdminsMessage BuildHigherAdminsMessage(const std::string& Message) {
    HigherAdminsMessage e;
        e.Message = Message;
    return e;
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

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Clase; 
};

inline Logged BuildLogged(std::uint8_t Clase) {
    Logged e;
        e.Clase = Clase;
    return e;
}

class RemoveDialogs : public ServerPacket {
public:
    RemoveDialogs();
    RemoveDialogs(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RemoveDialogs BuildRemoveDialogs() {
    RemoveDialogs e;

    return e;
}

class RemoveCharDialog : public ServerPacket {
public:
    RemoveCharDialog();
    RemoveCharDialog(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t CharIndex; 
};

inline RemoveCharDialog BuildRemoveCharDialog(std::int16_t CharIndex) {
    RemoveCharDialog e;
        e.CharIndex = CharIndex;
    return e;
}

class NavigateToggle : public ServerPacket {
public:
    NavigateToggle();
    NavigateToggle(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline NavigateToggle BuildNavigateToggle() {
    NavigateToggle e;

    return e;
}

class Disconnect : public ServerPacket {
public:
    Disconnect();
    Disconnect(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Disconnect BuildDisconnect() {
    Disconnect e;

    return e;
}

class CommerceEnd : public ServerPacket {
public:
    CommerceEnd();
    CommerceEnd(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline CommerceEnd BuildCommerceEnd() {
    CommerceEnd e;

    return e;
}

class BankEnd : public ServerPacket {
public:
    BankEnd();
    BankEnd(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline BankEnd BuildBankEnd() {
    BankEnd e;

    return e;
}

class CommerceInit : public ServerPacket {
public:
    CommerceInit();
    CommerceInit(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline CommerceInit BuildCommerceInit() {
    CommerceInit e;

    return e;
}

class BankInit : public ServerPacket {
public:
    BankInit();
    BankInit(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int32_t Banco; 
};

inline BankInit BuildBankInit(std::int32_t Banco) {
    BankInit e;
        e.Banco = Banco;
    return e;
}

class UserCommerceInit : public ServerPacket {
public:
    UserCommerceInit();
    UserCommerceInit(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string DestUserName; 
};

inline UserCommerceInit BuildUserCommerceInit(const std::string& DestUserName) {
    UserCommerceInit e;
        e.DestUserName = DestUserName;
    return e;
}

class UserCommerceEnd : public ServerPacket {
public:
    UserCommerceEnd();
    UserCommerceEnd(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline UserCommerceEnd BuildUserCommerceEnd() {
    UserCommerceEnd e;

    return e;
}

class UserOfferConfirm : public ServerPacket {
public:
    UserOfferConfirm();
    UserOfferConfirm(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline UserOfferConfirm BuildUserOfferConfirm() {
    UserOfferConfirm e;

    return e;
}

class CommerceChat : public ServerPacket {
public:
    CommerceChat();
    CommerceChat(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Chat; 
    std::uint8_t FontIndex; 
};

inline CommerceChat BuildCommerceChat(const std::string& Chat, std::uint8_t FontIndex) {
    CommerceChat e;
        e.Chat = Chat;
        e.FontIndex = FontIndex;
    return e;
}

class ShowBlacksmithForm : public ServerPacket {
public:
    ShowBlacksmithForm();
    ShowBlacksmithForm(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ShowBlacksmithForm BuildShowBlacksmithForm() {
    ShowBlacksmithForm e;

    return e;
}

class ShowCarpenterForm : public ServerPacket {
public:
    ShowCarpenterForm();
    ShowCarpenterForm(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ShowCarpenterForm BuildShowCarpenterForm() {
    ShowCarpenterForm e;

    return e;
}

class UpdateSta : public ServerPacket {
public:
    UpdateSta();
    UpdateSta(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t Value; 
};

inline UpdateSta BuildUpdateSta(std::int16_t Value) {
    UpdateSta e;
        e.Value = Value;
    return e;
}

class UpdateMana : public ServerPacket {
public:
    UpdateMana();
    UpdateMana(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t Value; 
};

inline UpdateMana BuildUpdateMana(std::int16_t Value) {
    UpdateMana e;
        e.Value = Value;
    return e;
}

class UpdateHP : public ServerPacket {
public:
    UpdateHP();
    UpdateHP(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t Value; 
};

inline UpdateHP BuildUpdateHP(std::int16_t Value) {
    UpdateHP e;
        e.Value = Value;
    return e;
}

class UpdateGold : public ServerPacket {
public:
    UpdateGold();
    UpdateGold(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int32_t Value; 
};

inline UpdateGold BuildUpdateGold(std::int32_t Value) {
    UpdateGold e;
        e.Value = Value;
    return e;
}

class UpdateBankGold : public ServerPacket {
public:
    UpdateBankGold();
    UpdateBankGold(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int32_t Value; 
};

inline UpdateBankGold BuildUpdateBankGold(std::int32_t Value) {
    UpdateBankGold e;
        e.Value = Value;
    return e;
}

class UpdateExp : public ServerPacket {
public:
    UpdateExp();
    UpdateExp(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int32_t Value; 
};

inline UpdateExp BuildUpdateExp(std::int32_t Value) {
    UpdateExp e;
        e.Value = Value;
    return e;
}

class ChangeMap : public ServerPacket {
public:
    ChangeMap();
    ChangeMap(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t Map; 
    std::int16_t Version; 
};

inline ChangeMap BuildChangeMap(std::int16_t Map, std::int16_t Version) {
    ChangeMap e;
        e.Map = Map;
        e.Version = Version;
    return e;
}

class PosUpdate : public ServerPacket {
public:
    PosUpdate();
    PosUpdate(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t X; 
    std::uint8_t Y; 
};

inline PosUpdate BuildPosUpdate(std::uint8_t X, std::uint8_t Y) {
    PosUpdate e;
        e.X = X;
        e.Y = Y;
    return e;
}

class ChatOverHead : public ServerPacket {
public:
    ChatOverHead();
    ChatOverHead(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Chat; 
    std::int16_t CharIndex; 
    std::uint8_t R; 
    std::uint8_t G; 
    std::uint8_t B; 
};

inline ChatOverHead BuildChatOverHead(const std::string& Chat, std::int16_t CharIndex, std::uint8_t R, std::uint8_t G, std::uint8_t B) {
    ChatOverHead e;
        e.Chat = Chat;
        e.CharIndex = CharIndex;
        e.R = R;
        e.G = G;
        e.B = B;
    return e;
}

class ConsoleMsg : public ServerPacket {
public:
    ConsoleMsg();
    ConsoleMsg(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Chat; 
    std::int16_t FontIndex; 
};

inline ConsoleMsg BuildConsoleMsg(const std::string& Chat, std::int16_t FontIndex) {
    ConsoleMsg e;
        e.Chat = Chat;
        e.FontIndex = FontIndex;
    return e;
}

class GuildChat : public ServerPacket {
public:
    GuildChat();
    GuildChat(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Chat; 
};

inline GuildChat BuildGuildChat(const std::string& Chat) {
    GuildChat e;
        e.Chat = Chat;
    return e;
}

class ShowMessageBox : public ServerPacket {
public:
    ShowMessageBox();
    ShowMessageBox(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Chat; 
};

inline ShowMessageBox BuildShowMessageBox(const std::string& Chat) {
    ShowMessageBox e;
        e.Chat = Chat;
    return e;
}

class UserIndexInServer : public ServerPacket {
public:
    UserIndexInServer();
    UserIndexInServer(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t UserIndex; 
};

inline UserIndexInServer BuildUserIndexInServer(std::int16_t UserIndex) {
    UserIndexInServer e;
        e.UserIndex = UserIndex;
    return e;
}

class UserCharIndexInServer : public ServerPacket {
public:
    UserCharIndexInServer();
    UserCharIndexInServer(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t CharIndex; 
};

inline UserCharIndexInServer BuildUserCharIndexInServer(std::int16_t CharIndex) {
    UserCharIndexInServer e;
        e.CharIndex = CharIndex;
    return e;
}

class CharacterCreate : public ServerPacket {
public:
    CharacterCreate();
    CharacterCreate(clsByteQueue* buffer);

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
    CharacterCreate e;
        e.CharIndex = CharIndex;
        e.Body = Body;
        e.Head = Head;
        e.Heading = Heading;
        e.X = X;
        e.Y = Y;
        e.Weapon = Weapon;
        e.Shield = Shield;
        e.Helmet = Helmet;
        e.FX = FX;
        e.FXLoops = FXLoops;
        e.Name = Name;
        e.NickColor = NickColor;
        e.Privileges = Privileges;
    return e;
}

class CharacterRemove : public ServerPacket {
public:
    CharacterRemove();
    CharacterRemove(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t CharIndex; 
};

inline CharacterRemove BuildCharacterRemove(std::int16_t CharIndex) {
    CharacterRemove e;
        e.CharIndex = CharIndex;
    return e;
}

class CharacterChangeNick : public ServerPacket {
public:
    CharacterChangeNick();
    CharacterChangeNick(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t CharIndex; 
    std::string NewName; 
};

inline CharacterChangeNick BuildCharacterChangeNick(std::int16_t CharIndex, const std::string& NewName) {
    CharacterChangeNick e;
        e.CharIndex = CharIndex;
        e.NewName = NewName;
    return e;
}

class CharacterMove : public ServerPacket {
public:
    CharacterMove();
    CharacterMove(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t CharIndex; 
    std::uint8_t X; 
    std::uint8_t Y; 
};

inline CharacterMove BuildCharacterMove(std::int16_t CharIndex, std::uint8_t X, std::uint8_t Y) {
    CharacterMove e;
        e.CharIndex = CharIndex;
        e.X = X;
        e.Y = Y;
    return e;
}

class ForceCharMove : public ServerPacket {
public:
    ForceCharMove();
    ForceCharMove(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Direction; 
};

inline ForceCharMove BuildForceCharMove(std::uint8_t Direction) {
    ForceCharMove e;
        e.Direction = Direction;
    return e;
}

class CharacterChange : public ServerPacket {
public:
    CharacterChange();
    CharacterChange(clsByteQueue* buffer);

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
    CharacterChange e;
        e.CharIndex = CharIndex;
        e.Body = Body;
        e.Head = Head;
        e.Heading = Heading;
        e.Weapon = Weapon;
        e.Shield = Shield;
        e.Helmet = Helmet;
        e.FX = FX;
        e.FXLoops = FXLoops;
    return e;
}

class ObjectCreate : public ServerPacket {
public:
    ObjectCreate();
    ObjectCreate(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t X; 
    std::uint8_t Y; 
    std::int16_t GrhIndex; 
};

inline ObjectCreate BuildObjectCreate(std::uint8_t X, std::uint8_t Y, std::int16_t GrhIndex) {
    ObjectCreate e;
        e.X = X;
        e.Y = Y;
        e.GrhIndex = GrhIndex;
    return e;
}

class ObjectDelete : public ServerPacket {
public:
    ObjectDelete();
    ObjectDelete(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t X; 
    std::uint8_t Y; 
};

inline ObjectDelete BuildObjectDelete(std::uint8_t X, std::uint8_t Y) {
    ObjectDelete e;
        e.X = X;
        e.Y = Y;
    return e;
}

class BlockPosition : public ServerPacket {
public:
    BlockPosition();
    BlockPosition(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t X; 
    std::uint8_t Y; 
    bool Blocked; 
};

inline BlockPosition BuildBlockPosition(std::uint8_t X, std::uint8_t Y, bool Blocked) {
    BlockPosition e;
        e.X = X;
        e.Y = Y;
        e.Blocked = Blocked;
    return e;
}

class PlayMidi : public ServerPacket {
public:
    PlayMidi();
    PlayMidi(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t MidiID; 
    std::int16_t Loops; 
};

inline PlayMidi BuildPlayMidi(std::int16_t MidiID, std::int16_t Loops) {
    PlayMidi e;
        e.MidiID = MidiID;
        e.Loops = Loops;
    return e;
}

class PlayWave : public ServerPacket {
public:
    PlayWave();
    PlayWave(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t WaveID; 
    std::uint8_t X; 
    std::uint8_t Y; 
};

inline PlayWave BuildPlayWave(std::uint8_t WaveID, std::uint8_t X, std::uint8_t Y) {
    PlayWave e;
        e.WaveID = WaveID;
        e.X = X;
        e.Y = Y;
    return e;
}

class GuildList : public ServerPacket {
public:
    GuildList();
    GuildList(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Data; 
};

inline GuildList BuildGuildList(const std::string& Data) {
    GuildList e;
        e.Data = Data;
    return e;
}

class AreaChanged : public ServerPacket {
public:
    AreaChanged();
    AreaChanged(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t X; 
    std::uint8_t Y; 
};

inline AreaChanged BuildAreaChanged(std::uint8_t X, std::uint8_t Y) {
    AreaChanged e;
        e.X = X;
        e.Y = Y;
    return e;
}

class PauseToggle : public ServerPacket {
public:
    PauseToggle();
    PauseToggle(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline PauseToggle BuildPauseToggle() {
    PauseToggle e;

    return e;
}

class RainToggle : public ServerPacket {
public:
    RainToggle();
    RainToggle(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline RainToggle BuildRainToggle() {
    RainToggle e;

    return e;
}

class CreateFX : public ServerPacket {
public:
    CreateFX();
    CreateFX(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t CharIndex; 
    std::int16_t FX; 
    std::int16_t FXLoops; 
};

inline CreateFX BuildCreateFX(std::int16_t CharIndex, std::int16_t FX, std::int16_t FXLoops) {
    CreateFX e;
        e.CharIndex = CharIndex;
        e.FX = FX;
        e.FXLoops = FXLoops;
    return e;
}

class UpdateUserStats : public ServerPacket {
public:
    UpdateUserStats();
    UpdateUserStats(clsByteQueue* buffer);

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
    UpdateUserStats e;
        e.MaxHp = MaxHp;
        e.MinHp = MinHp;
        e.MaxMan = MaxMan;
        e.MinMan = MinMan;
        e.MaxSta = MaxSta;
        e.MinSta = MinSta;
        e.Gld = Gld;
        e.Elv = Elv;
        e.Elu = Elu;
        e.Exp = Exp;
    return e;
}

class WorkRequestTarget : public ServerPacket {
public:
    WorkRequestTarget();
    WorkRequestTarget(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Skill; 
};

inline WorkRequestTarget BuildWorkRequestTarget(std::uint8_t Skill) {
    WorkRequestTarget e;
        e.Skill = Skill;
    return e;
}

class ChangeInventorySlot : public ServerPacket {
public:
    ChangeInventorySlot();
    ChangeInventorySlot(clsByteQueue* buffer);

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
    ChangeInventorySlot e;
        e.Slot = Slot;
        e.ObjIndex = ObjIndex;
        e.ObjName = ObjName;
        e.Amount = Amount;
        e.Equiped = Equiped;
        e.GrhIndex = GrhIndex;
        e.ObjType = ObjType;
        e.MaxHit = MaxHit;
        e.MinHit = MinHit;
        e.MaxDef = MaxDef;
        e.MinDef = MinDef;
        e.ObjSalePrice = ObjSalePrice;
    return e;
}

class ChangeBankSlot : public ServerPacket {
public:
    ChangeBankSlot();
    ChangeBankSlot(clsByteQueue* buffer);

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
    ChangeBankSlot e;
        e.Slot = Slot;
        e.ObjIndex = ObjIndex;
        e.ObjName = ObjName;
        e.Amount = Amount;
        e.GrhIndex = GrhIndex;
        e.ObjType = ObjType;
        e.MaxHit = MaxHit;
        e.MinHit = MinHit;
        e.MaxDef = MaxDef;
        e.MinDef = MinDef;
        e.ObjSalePrice = ObjSalePrice;
    return e;
}

class ChangeSpellSlot : public ServerPacket {
public:
    ChangeSpellSlot();
    ChangeSpellSlot(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Slot; 
    std::int16_t SpellID; 
    std::string Name; 
};

inline ChangeSpellSlot BuildChangeSpellSlot(std::uint8_t Slot, std::int16_t SpellID, const std::string& Name) {
    ChangeSpellSlot e;
        e.Slot = Slot;
        e.SpellID = SpellID;
        e.Name = Name;
    return e;
}

class Atributes : public ServerPacket {
public:
    Atributes();
    Atributes(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Fuerza; 
    std::uint8_t Agilidad; 
    std::uint8_t Inteligencia; 
    std::uint8_t Carisma; 
    std::uint8_t Constitucion; 
};

inline Atributes BuildAtributes(std::uint8_t Fuerza, std::uint8_t Agilidad, std::uint8_t Inteligencia, std::uint8_t Carisma, std::uint8_t Constitucion) {
    Atributes e;
        e.Fuerza = Fuerza;
        e.Agilidad = Agilidad;
        e.Inteligencia = Inteligencia;
        e.Carisma = Carisma;
        e.Constitucion = Constitucion;
    return e;
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
    RestOK e;

    return e;
}

class ErrorMsg : public ServerPacket {
public:
    ErrorMsg();
    ErrorMsg(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Message; 
};

inline ErrorMsg BuildErrorMsg(const std::string& Message) {
    ErrorMsg e;
        e.Message = Message;
    return e;
}

class Blind : public ServerPacket {
public:
    Blind();
    Blind(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Blind BuildBlind() {
    Blind e;

    return e;
}

class Dumb : public ServerPacket {
public:
    Dumb();
    Dumb(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Dumb BuildDumb() {
    Dumb e;

    return e;
}

class ShowSignal : public ServerPacket {
public:
    ShowSignal();
    ShowSignal(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Texto; 
    std::int16_t Grh; 
};

inline ShowSignal BuildShowSignal(const std::string& Texto, std::int16_t Grh) {
    ShowSignal e;
        e.Texto = Texto;
        e.Grh = Grh;
    return e;
}

class ChangeNPCInventorySlot : public ServerPacket {
public:
    ChangeNPCInventorySlot();
    ChangeNPCInventorySlot(clsByteQueue* buffer);

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
    ChangeNPCInventorySlot e;
        e.Slot = Slot;
        e.ObjName = ObjName;
        e.Amount = Amount;
        e.Price = Price;
        e.GrhIndex = GrhIndex;
        e.ObjIndex = ObjIndex;
        e.ObjType = ObjType;
        e.MaxHit = MaxHit;
        e.MinHit = MinHit;
        e.MaxDef = MaxDef;
        e.MinDef = MinDef;
    return e;
}

class UpdateHungerAndThirst : public ServerPacket {
public:
    UpdateHungerAndThirst();
    UpdateHungerAndThirst(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t MaxAgu; 
    std::uint8_t MinAgu; 
    std::uint8_t MaxHam; 
    std::uint8_t MinHam; 
};

inline UpdateHungerAndThirst BuildUpdateHungerAndThirst(std::uint8_t MaxAgu, std::uint8_t MinAgu, std::uint8_t MaxHam, std::uint8_t MinHam) {
    UpdateHungerAndThirst e;
        e.MaxAgu = MaxAgu;
        e.MinAgu = MinAgu;
        e.MaxHam = MaxHam;
        e.MinHam = MinHam;
    return e;
}

class Fame : public ServerPacket {
public:
    Fame();
    Fame(clsByteQueue* buffer);

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
    Fame e;
        e.Asesino = Asesino;
        e.Bandido = Bandido;
        e.Burgues = Burgues;
        e.Ladron = Ladron;
        e.Noble = Noble;
        e.Plebe = Plebe;
        e.Promedio = Promedio;
    return e;
}

class MiniStats : public ServerPacket {
public:
    MiniStats();
    MiniStats(clsByteQueue* buffer);

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
    MiniStats e;
        e.CiudadanosMatados = CiudadanosMatados;
        e.CriminalesMatados = CriminalesMatados;
        e.UsuariosMatados = UsuariosMatados;
        e.NpcsMuertos = NpcsMuertos;
        e.Clase = Clase;
        e.Pena = Pena;
    return e;
}

class LevelUp : public ServerPacket {
public:
    LevelUp();
    LevelUp(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t SkillPoints; 
};

inline LevelUp BuildLevelUp(std::int16_t SkillPoints) {
    LevelUp e;
        e.SkillPoints = SkillPoints;
    return e;
}

class AddForumMsg : public ServerPacket {
public:
    AddForumMsg();
    AddForumMsg(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int32_t ForumType; 
    std::string Title; 
    std::string Author; 
    std::string Message; 
};

inline AddForumMsg BuildAddForumMsg(std::int32_t ForumType, const std::string& Title, const std::string& Author, const std::string& Message) {
    AddForumMsg e;
        e.ForumType = ForumType;
        e.Title = Title;
        e.Author = Author;
        e.Message = Message;
    return e;
}

class ShowForumForm : public ServerPacket {
public:
    ShowForumForm();
    ShowForumForm(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Visibilidad; 
    std::uint8_t CanMakeSticky; 
};

inline ShowForumForm BuildShowForumForm(std::uint8_t Visibilidad, std::uint8_t CanMakeSticky) {
    ShowForumForm e;
        e.Visibilidad = Visibilidad;
        e.CanMakeSticky = CanMakeSticky;
    return e;
}

class SetInvisible : public ServerPacket {
public:
    SetInvisible();
    SetInvisible(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t charIndex; 
    bool invisible; 
};

inline SetInvisible BuildSetInvisible(std::int16_t charIndex, bool invisible) {
    SetInvisible e;
        e.charIndex = charIndex;
        e.invisible = invisible;
    return e;
}

class DiceRoll : public ServerPacket {
public:
    DiceRoll();
    DiceRoll(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Fuerza; 
    std::uint8_t Agilidad; 
    std::uint8_t Inteligencia; 
    std::uint8_t Carisma; 
    std::uint8_t Constitucion; 
};

inline DiceRoll BuildDiceRoll(std::uint8_t Fuerza, std::uint8_t Agilidad, std::uint8_t Inteligencia, std::uint8_t Carisma, std::uint8_t Constitucion) {
    DiceRoll e;
        e.Fuerza = Fuerza;
        e.Agilidad = Agilidad;
        e.Inteligencia = Inteligencia;
        e.Carisma = Carisma;
        e.Constitucion = Constitucion;
    return e;
}

class MeditateToggle : public ServerPacket {
public:
    MeditateToggle();
    MeditateToggle(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline MeditateToggle BuildMeditateToggle() {
    MeditateToggle e;

    return e;
}

class BlindNoMore : public ServerPacket {
public:
    BlindNoMore();
    BlindNoMore(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline BlindNoMore BuildBlindNoMore() {
    BlindNoMore e;

    return e;
}

class DumbNoMore : public ServerPacket {
public:
    DumbNoMore();
    DumbNoMore(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline DumbNoMore BuildDumbNoMore() {
    DumbNoMore e;

    return e;
}

class SendSkills : public ServerPacket {
public:
    SendSkills();
    SendSkills(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::vector<std::uint8_t> Skills; 
};

inline SendSkills BuildSendSkills(std::vector<std::uint8_t> Skills ) {
    SendSkills e;
        e.Skills = Skills;
    return e;
}

class TrainerCreatureList : public ServerPacket {
public:
    TrainerCreatureList();
    TrainerCreatureList(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Data; 
};

inline TrainerCreatureList BuildTrainerCreatureList(const std::string& Data) {
    TrainerCreatureList e;
        e.Data = Data;
    return e;
}

class GuildNews : public ServerPacket {
public:
    GuildNews();
    GuildNews(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string News; 
    std::string EnemiesList; 
    std::string AlliesList; 
};

inline GuildNews BuildGuildNews(const std::string& News, const std::string& EnemiesList, const std::string& AlliesList) {
    GuildNews e;
        e.News = News;
        e.EnemiesList = EnemiesList;
        e.AlliesList = AlliesList;
    return e;
}

class OfferDetails : public ServerPacket {
public:
    OfferDetails();
    OfferDetails(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Details; 
};

inline OfferDetails BuildOfferDetails(const std::string& Details) {
    OfferDetails e;
        e.Details = Details;
    return e;
}

class AlianceProposalsList : public ServerPacket {
public:
    AlianceProposalsList();
    AlianceProposalsList(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Data; 
};

inline AlianceProposalsList BuildAlianceProposalsList(const std::string& Data) {
    AlianceProposalsList e;
        e.Data = Data;
    return e;
}

class PeaceProposalsList : public ServerPacket {
public:
    PeaceProposalsList();
    PeaceProposalsList(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Data; 
};

inline PeaceProposalsList BuildPeaceProposalsList(const std::string& Data) {
    PeaceProposalsList e;
        e.Data = Data;
    return e;
}

class CharacterInfo : public ServerPacket {
public:
    CharacterInfo();
    CharacterInfo(clsByteQueue* buffer);

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
    CharacterInfo e;
        e.CharName = CharName;
        e.Race = Race;
        e.Class = Class;
        e.Gender = Gender;
        e.Level = Level;
        e.Gold = Gold;
        e.Bank = Bank;
        e.Reputation = Reputation;
        e.PreviousPetitions = PreviousPetitions;
        e.CurrentGuild = CurrentGuild;
        e.PreviousGuilds = PreviousGuilds;
        e.RoyalArmy = RoyalArmy;
        e.ChaosLegion = ChaosLegion;
        e.CiudadanosMatados = CiudadanosMatados;
        e.CriminalesMatados = CriminalesMatados;
    return e;
}

class GuildLeaderInfo : public ServerPacket {
public:
    GuildLeaderInfo();
    GuildLeaderInfo(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string GuildList; 
    std::string MemberList; 
    std::string GuildNews; 
    std::string JoinRequests; 
};

inline GuildLeaderInfo BuildGuildLeaderInfo(const std::string& GuildList, const std::string& MemberList, const std::string& GuildNews, const std::string& JoinRequests) {
    GuildLeaderInfo e;
        e.GuildList = GuildList;
        e.MemberList = MemberList;
        e.GuildNews = GuildNews;
        e.JoinRequests = JoinRequests;
    return e;
}

class GuildMemberInfo : public ServerPacket {
public:
    GuildMemberInfo();
    GuildMemberInfo(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string GuildList; 
    std::string MemberList; 
};

inline GuildMemberInfo BuildGuildMemberInfo(const std::string& GuildList, const std::string& MemberList) {
    GuildMemberInfo e;
        e.GuildList = GuildList;
        e.MemberList = MemberList;
    return e;
}

class GuildDetails : public ServerPacket {
public:
    GuildDetails();
    GuildDetails(clsByteQueue* buffer);

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
    GuildDetails e;
        e.GuildName = GuildName;
        e.Founder = Founder;
        e.FoundationDate = FoundationDate;
        e.Leader = Leader;
        e.URL = URL;
        e.MemberCount = MemberCount;
        e.ElectionsOpen = ElectionsOpen;
        e.Aligment = Aligment;
        e.EnemiesCount = EnemiesCount;
        e.AlliesCount = AlliesCount;
        e.AntifactionPoints = AntifactionPoints;
        e.Codex = Codex;
        e.GuildDesc = GuildDesc;
    return e;
}

class ShowGuildFundationForm : public ServerPacket {
public:
    ShowGuildFundationForm();
    ShowGuildFundationForm(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ShowGuildFundationForm BuildShowGuildFundationForm() {
    ShowGuildFundationForm e;

    return e;
}

class ParalizeOK : public ServerPacket {
public:
    ParalizeOK();
    ParalizeOK(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ParalizeOK BuildParalizeOK() {
    ParalizeOK e;

    return e;
}

class ShowUserRequest : public ServerPacket {
public:
    ShowUserRequest();
    ShowUserRequest(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Details; 
};

inline ShowUserRequest BuildShowUserRequest(const std::string& Details) {
    ShowUserRequest e;
        e.Details = Details;
    return e;
}

class TradeOK : public ServerPacket {
public:
    TradeOK();
    TradeOK(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline TradeOK BuildTradeOK() {
    TradeOK e;

    return e;
}

class BankOK : public ServerPacket {
public:
    BankOK();
    BankOK(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline BankOK BuildBankOK() {
    BankOK e;

    return e;
}

class ChangeUserTradeSlot : public ServerPacket {
public:
    ChangeUserTradeSlot();
    ChangeUserTradeSlot(clsByteQueue* buffer);

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
    ChangeUserTradeSlot e;
        e.OfferSlot = OfferSlot;
        e.ObjIndex = ObjIndex;
        e.Amount = Amount;
        e.GrhIndex = GrhIndex;
        e.ObjType = ObjType;
        e.MaxHit = MaxHit;
        e.MinHit = MinHit;
        e.MaxDef = MaxDef;
        e.MinDef = MinDef;
        e.Price = Price;
        e.ObjName = ObjName;
    return e;
}

class SendNight : public ServerPacket {
public:
    SendNight();
    SendNight(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    bool Night; 
};

inline SendNight BuildSendNight(bool Night) {
    SendNight e;
        e.Night = Night;
    return e;
}

class Pong : public ServerPacket {
public:
    Pong();
    Pong(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline Pong BuildPong() {
    Pong e;

    return e;
}

class UpdateTagAndStatus : public ServerPacket {
public:
    UpdateTagAndStatus();
    UpdateTagAndStatus(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::int16_t CharIndex; 
    std::uint8_t NickColor; 
    std::string Tag; 
};

inline UpdateTagAndStatus BuildUpdateTagAndStatus(std::int16_t CharIndex, std::uint8_t NickColor, const std::string& Tag) {
    UpdateTagAndStatus e;
        e.CharIndex = CharIndex;
        e.NickColor = NickColor;
        e.Tag = Tag;
    return e;
}

class SpawnList : public ServerPacket {
public:
    SpawnList();
    SpawnList(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Data; 
};

inline SpawnList BuildSpawnList(const std::string& Data) {
    SpawnList e;
        e.Data = Data;
    return e;
}

class ShowSOSForm : public ServerPacket {
public:
    ShowSOSForm();
    ShowSOSForm(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Data; 
};

inline ShowSOSForm BuildShowSOSForm(const std::string& Data) {
    ShowSOSForm e;
        e.Data = Data;
    return e;
}

class ShowMOTDEditionForm : public ServerPacket {
public:
    ShowMOTDEditionForm();
    ShowMOTDEditionForm(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Data; 
};

inline ShowMOTDEditionForm BuildShowMOTDEditionForm(const std::string& Data) {
    ShowMOTDEditionForm e;
        e.Data = Data;
    return e;
}

class ShowGMPanelForm : public ServerPacket {
public:
    ShowGMPanelForm();
    ShowGMPanelForm(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ShowGMPanelForm BuildShowGMPanelForm() {
    ShowGMPanelForm e;

    return e;
}

class UserNameList : public ServerPacket {
public:
    UserNameList();
    UserNameList(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Data; 
};

inline UserNameList BuildUserNameList(const std::string& Data) {
    UserNameList e;
        e.Data = Data;
    return e;
}

class ShowDenounces : public ServerPacket {
public:
    ShowDenounces();
    ShowDenounces(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::string Data; 
};

inline ShowDenounces BuildShowDenounces(const std::string& Data) {
    ShowDenounces e;
        e.Data = Data;
    return e;
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
    RecordDetails e;
        e.Creador = Creador;
        e.Motivo = Motivo;
        e.Online = Online;
        e.IP = IP;
        e.OnlineTime = OnlineTime;
        e.Obs = Obs;
    return e;
}

class ShowGuildAlign : public ServerPacket {
public:
    ShowGuildAlign();
    ShowGuildAlign(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline ShowGuildAlign BuildShowGuildAlign() {
    ShowGuildAlign e;

    return e;
}

class ShowPartyForm : public ServerPacket {
public:
    ShowPartyForm();
    ShowPartyForm(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t EsLider; 
    std::string Data; 
    std::int32_t Exp; 
};

inline ShowPartyForm BuildShowPartyForm(std::uint8_t EsLider, const std::string& Data, std::int32_t Exp) {
    ShowPartyForm e;
        e.EsLider = EsLider;
        e.Data = Data;
        e.Exp = Exp;
    return e;
}

class UpdateStrenghtAndDexterity : public ServerPacket {
public:
    UpdateStrenghtAndDexterity();
    UpdateStrenghtAndDexterity(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Fuerza; 
    std::uint8_t Agilidad; 
};

inline UpdateStrenghtAndDexterity BuildUpdateStrenghtAndDexterity(std::uint8_t Fuerza, std::uint8_t Agilidad) {
    UpdateStrenghtAndDexterity e;
        e.Fuerza = Fuerza;
        e.Agilidad = Agilidad;
    return e;
}

class UpdateStrenght : public ServerPacket {
public:
    UpdateStrenght();
    UpdateStrenght(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Fuerza; 
};

inline UpdateStrenght BuildUpdateStrenght(std::uint8_t Fuerza) {
    UpdateStrenght e;
        e.Fuerza = Fuerza;
    return e;
}

class UpdateDexterity : public ServerPacket {
public:
    UpdateDexterity();
    UpdateDexterity(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Agilidad; 
};

inline UpdateDexterity BuildUpdateDexterity(std::uint8_t Agilidad) {
    UpdateDexterity e;
        e.Agilidad = Agilidad;
    return e;
}

class AddSlots : public ServerPacket {
public:
    AddSlots();
    AddSlots(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Mochila; 
};

inline AddSlots BuildAddSlots(std::uint8_t Mochila) {
    AddSlots e;
        e.Mochila = Mochila;
    return e;
}

class MultiMessage : public ServerPacket {
public:
    MultiMessage();
    MultiMessage(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline MultiMessage BuildMultiMessage() {
    MultiMessage e;

    return e;
}

class StopWorking : public ServerPacket {
public:
    StopWorking();
    StopWorking(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);


};

inline StopWorking BuildStopWorking() {
    StopWorking e;

    return e;
}

class CancelOfferItem : public ServerPacket {
public:
    CancelOfferItem();
    CancelOfferItem(clsByteQueue* buffer);

    virtual void serialize(clsByteQueue* buffer) const;
    virtual void dispatch(PacketHandler* d);

    std::uint8_t Slot; 
};

inline CancelOfferItem BuildCancelOfferItem(std::uint8_t Slot) {
    CancelOfferItem e;
        e.Slot = Slot;
    return e;
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

