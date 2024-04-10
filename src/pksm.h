struct pkx
{
    int species;
    int form;
};

enum Generation
{
    GEN_FOUR,
    GEN_FIVE,
    GEN_SIX,
    GEN_SEVEN,
    GEN_LGPE,
    GEN_EIGHT,
    GEN_THREE,
    GEN_ONE,
    GEN_TWO
};

struct directory
{
    int count;
    char** files;
};

enum PKX_Field
{
    OT_NAME,
    TID,
    SID,
    SHINY,
    LANGUAGE,
    MET_LOCATION,
    MOVE,
    BALL,
    LEVEL,
    GENDER,
    ABILITY,
    IV_HP,
    IV_ATK,
    IV_DEF,
    IV_SPATK,
    IV_SPDEF,
    IV_SPEED,
    NICKNAME,
    ITEM,
    POKERUS,
    EGG_DAY,
    EGG_MONTH,
    EGG_YEAR,
    MET_DAY,
    MET_MONTH,
    MET_YEAR,
    FORM,
    EV_HP,
    EV_ATK,
    EV_DEF,
    EV_SPATK,
    EV_SPDEF,
    EV_SPEED,
    SPECIES,
    PID,
    NATURE,
    FATEFUL,
    PP,
    PP_UPS,
    EGG,
    NICKNAMED,
    EGG_LOCATION,
    MET_LEVEL,
    OT_GENDER,
    ORIGINAL_GAME
};

enum SAV_Field
{
    SAV_OT_NAME,
    SAV_TID,
    SAV_SID,
    SAV_GENDER,
    SAV_COUNTRY,
    SAV_SUBREGION,
    SAV_REGION,
    SAV_LANGUAGE,
    SAV_MONEY,
    SAV_BP,
    SAV_HOURS,
    SAV_MINUTES,
    SAV_SECONDS,
    SAV_ITEM
};

enum SAV_MaxField
{
    MAX_SLOTS,
    MAX_BOXES,
    MAX_WONDER_CARDS,
    MAX_FORM,
    MAX_IN_POUCH
};

enum SAV_CheckValue
{
    SAV_VALUE_SPECIES,
    SAV_VALUE_MOVE,
    SAV_VALUE_ITEM,
    SAV_VALUE_ABILITY,
    SAV_VALUE_BALL
};

enum Pouch
{
    NormalItem,
    KeyItem,
    TM,
    Mail,
    Medicine,
    Berry,
    Ball,
    Battle,
    Candy,
    ZCrystals
};

struct JSON
{
    void* dummy;
};

enum Ribbon 
{
    RIB_ChampionKalos,
    RIB_ChampionG3Hoenn,
    RIB_ChampionSinnoh,
    RIB_BestFriends,
    RIB_Training,
    RIB_BattlerSkillful,
    RIB_BattlerExpert,
    RIB_Effort,
    RIB_Alert,
    RIB_Shock,
    RIB_Downcast,
    RIB_Careless,
    RIB_Relax,
    RIB_Snooze,
    RIB_Smile,
    RIB_Gorgeous,
    RIB_Royal,
    RIB_GorgeousRoyal,
    RIB_Artist,
    RIB_Footprint,
    RIB_Record,
    RIB_Legend,
    RIB_Country,
    RIB_National,
    RIB_Earth,
    RIB_World,
    RIB_Classic,
    RIB_Premier,
    RIB_Event,
    RIB_Birthday,
    RIB_Special,
    RIB_Souvenir,
    RIB_Wishing,
    RIB_ChampionBattle,
    RIB_ChampionRegional,
    RIB_ChampionNational,
    RIB_ChampionWorld,
    RIB_MemoryContest,
    RIB_MemoryBattle,
    RIB_ChampionG6Hoenn,
    RIB_ContestStar,
    RIB_MasterCoolness,
    RIB_MasterBeauty,
    RIB_MasterCuteness,
    RIB_MasterCleverness,
    RIB_MasterToughness,
    RIB_G3Cool,
    RIB_G3CoolSuper,
    RIB_G3CoolHyper,
    RIB_G3CoolMaster,
    RIB_G3Beauty,
    RIB_G3BeautySuper,
    RIB_G3BeautyHyper,
    RIB_G3BeautyMaster,
    RIB_G3Cute,
    RIB_G3CuteSuper,
    RIB_G3CuteHyper,
    RIB_G3CuteMaster,
    RIB_G3Smart,
    RIB_G3SmartSuper,
    RIB_G3SmartHyper,
    RIB_G3SmartMaster,
    RIB_G3Tough,
    RIB_G3ToughSuper,
    RIB_G3ToughHyper,
    RIB_G3ToughMaster,
    RIB_G4Cool,
    RIB_G4CoolSuper,
    RIB_G4CoolHyper,
    RIB_G4CoolMaster,
    RIB_G4Beauty,
    RIB_G4BeautySuper,
    RIB_G4BeautyHyper,
    RIB_G4BeautyMaster,
    RIB_G4Cute,
    RIB_G4CuteSuper,
    RIB_G4CuteHyper,
    RIB_G4CuteMaster,
    RIB_G4Smart,
    RIB_G4SmartSuper,
    RIB_G4SmartHyper,
    RIB_G4SmartMaster,
    RIB_G4Tough,
    RIB_G4ToughSuper,
    RIB_G4ToughHyper,
    RIB_G4ToughMaster,
    RIB_Winning,
    RIB_Victory,
    RIB_Ability,
    RIB_AbilityGreat,
    RIB_AbilityDouble,
    RIB_AbilityMulti,
    RIB_AbilityPair,
    RIB_AbilityWorld,
    RIB_ChampionAlola,
    RIB_BattleRoyale,
    RIB_BattleTreeGreat,
    RIB_BattleTreeMaster,
    RIB_ChampionGalar,
    RIB_TowerMaster,
    RIB_MasterRank,
    RIB_MarkLunchtime,
    RIB_MarkSleepyTime,
    RIB_MarkDusk,
    RIB_MarkDawn,
    RIB_MarkCloudy,
    RIB_MarkRainy,
    RIB_MarkStormy,
    RIB_MarkSnowy,
    RIB_MarkBlizzard,
    RIB_MarkDry,
    RIB_MarkSandstorm,
    RIB_MarkMisty,
    RIB_MarkDestiny,
    RIB_MarkFishing,
    RIB_MarkCurry,
    RIB_MarkUncommon,
    RIB_MarkRare,
    RIB_MarkRowdy,
    RIB_MarkAbsentMinded,
    RIB_MarkJittery,
    RIB_MarkExcited,
    RIB_MarkCharismatic,
    RIB_MarkCalmness,
    RIB_MarkIntense,
    RIB_MarkZonedOut,
    RIB_MarkJoyful,
    RIB_MarkAngry,
    RIB_MarkSmiley,
    RIB_MarkTeary,
    RIB_MarkUpbeat,
    RIB_MarkPeeved,
    RIB_MarkIntellectual,
    RIB_MarkFerocious,
    RIB_MarkCrafty,
    RIB_MarkScowling,
    RIB_MarkKindly,
    RIB_MarkFlustered,
    RIB_MarkPumpedUp,
    RIB_MarkZeroEnergy,
    RIB_MarkPrideful,
    RIB_MarkUnsure,
    RIB_MarkHumble,
    RIB_MarkThorny,
    RIB_MarkVigor,
    RIB_MarkSlump,
    RIB_G4CoolGreat = RIB_G4CoolSuper,
    RIB_G4CoolUltra = RIB_G4CoolHyper,
    RIB_G4BeautyGreat = RIB_G4BeautySuper,
    RIB_G4BeautyUltra = RIB_G4BeautyHyper,
    RIB_G4CuteGreat = RIB_G4CuteSuper,
    RIB_G4CuteUltra = RIB_G4CuteHyper,
    RIB_G4SmartGreat = RIB_G4SmartSuper,
    RIB_G4SmartUltra = RIB_G4SmartHyper,
    RIB_G4ToughGreat = RIB_G4ToughSuper,
    RIB_G4ToughUltra = RIB_G4ToughHyper
};

int gui_choice(char* message);
void gui_warn(char* warning);
void gui_splash(char* notification);
int gui_menu_6x5(
    char* question, int options, char** labels, struct pkx* pokemon, enum Generation generation);
int gui_menu_20x2(char* question, int options, char** labels);
void gui_keyboard(char* out, char* hint, int maxChars);
void gui_numpad(unsigned int* out, char* hint, int maxDigits);
int gui_boxes(int* fromStorage, int* box, int* slot, int doCrypt);

int sav_gbo(void);
int sav_sbo(void);
void sav_box_decrypt(void);
void sav_box_encrypt(void);
void sav_get_pkx(char* data, int box, int slot);
void sav_inject_pkx(char* data, enum Generation type, int box, int slot, int doTradeEdits);
void sav_inject_wcx(char* data, enum Generation type, int slot, int alternateFormat);
int sav_wcx_free_slot(void);
int sav_get_value(enum SAV_Field field, ...);
int sav_get_max(enum SAV_MaxField field, ...);
int sav_check_value(enum SAV_CheckValue field, int value);
void sav_register_pkx_dex(char* data, enum Generation gen);
void party_get_pkx(char* data, int slot);
void party_inject_pkx(char* data, enum Generation type, int slot);
void bank_inject_pkx(char* data, enum Generation type, int box, int slot);

char* bank_get_pkx(enum Generation* type, int box, int slot);
int bank_get_size(void);
void bank_select(void);

void sav_get_data(char* dataOut, unsigned int size, int off1, int off2);
void sav_set_data(char* data, unsigned int size, int off1, int off2);
int sav_get_bit(int off1, int off2, int bit);
void sav_set_bit(int bitVal, int off1, int off2, int bit);
char sav_get_byte(int off1, int off2);
void sav_set_byte(char data, int off1, int off2);
short sav_get_short(int off1, int off2);
void sav_set_short(short data, int off1, int off2);
int sav_get_int(int off1, int off2);
void sav_set_int(int data, int off1, int off2);
char* sav_get_string(int off1, int off2, unsigned int codepoints);
void sav_set_string(char* string, int off1, int off2, unsigned int codepoints);
int sav_get_palpark(char** out, int* outSize);
int sav_set_palpark(char** data, enum Generation* gen, int inSize);

void pkx_decrypt(char* data, enum Generation type, int isParty);
void pkx_encrypt(char* data, enum Generation type, int isParty);
int pkx_box_size(enum Generation gen);
int pkx_party_size(enum Generation gen);
void pkx_generate(char* data, int species);
int pkx_is_valid(char* data, enum Generation gen);
void pkx_set_value(char* data, enum Generation gen, enum PKX_Field field, ...);
unsigned int pkx_get_value(char* data, enum Generation gen, enum PKX_Field field, ...);
void pkx_update_party_data(char* data, enum Generation gen);
int pkx_ribbon_exists(enum Generation gen, enum Ribbon ribbon);
int pkx_get_ribbon(char* data, enum Generation gen, enum Ribbon ribbon);
void pkx_set_ribbon(char* data, enum Generation gen, enum Ribbon ribbon, int hasRibbon);

char* current_directory(void);
struct directory* read_directory(char* dir);
void delete_directory(struct directory* dir);
char* save_path(void);

char* cfg_default_ot(enum Generation gen);
unsigned short cfg_default_tid(enum Generation gen);
unsigned short cfg_default_sid(enum Generation gen);
int cfg_default_day(void);
int cfg_default_month(void);
int cfg_default_year(void);

char* net_ip(void);
int net_tcp_recv(char* buffer, int size, int* received);
int net_tcp_send(char* ip, int port, char* buffer, int size);
int net_udp_recv(char* buffer, int size, int* received);
int fetch_web_content(char** out, int* outSize, char* url);

char* i18n_species(int species);
char* i18n_form(int gameVersion, int species, int form);
int max_pp(enum Generation gen, int move, int ppUps);

char* ucs2_to_utf8(char* data);
char* utf8_to_ucs2(char* data);
void base64_decode(unsigned char** out, int* outSize, char* data, int size);
void base64_encode(char** out, int* outSize, unsigned char* data, int size);
void bz2_decompress(unsigned char** out, int* outSize, unsigned char* data, int size);
void bz2_compress(unsigned char** out, int* outSize, unsigned char* data, int size);

struct JSON* json_new(void);
void json_parse(struct JSON* out, char* data);
void json_delete(struct JSON* freed);
int json_is_valid(struct JSON* check);
int json_is_int(struct JSON* check);
int json_is_bool(struct JSON* check);
int json_is_string(struct JSON* check);
int json_is_array(struct JSON* check);
int json_is_object(struct JSON* check);
int json_get_int(struct JSON* get);
int json_get_bool(struct JSON* get);
char* json_get_string(struct JSON* get);
int json_array_size(struct JSON* get);
struct JSON* json_array_element(struct JSON* array, int index);
int json_object_contains(struct JSON* get, char* elemName);
struct JSON* json_object_element(struct JSON* object, char* elemName);
