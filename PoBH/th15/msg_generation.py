Satanae = 1
Reimu = 2
God_Reimu = 3
VodkAlice = 4

def is_character_player(character_name, line_number):
    dialogTypes = ["b", "X", "e"]
    if character_name[line_number] == "Sa":
        return Satanae
    if character_name[line_number] == "R":
        return Reimu
    if character_name[line_number] == "GR":
        return God_Reimu
    if character_name[line_number] == "V":
        return VodkAlice
    if character_name[line_number] == None :
        return 0
    for dialogType in dialogTypes:
        if character_name[line_number] == dialogType:
            return -1
    return 10

def getPosX_with_char(character):
    if character == Satanae:
        return 110.0
    if character == Reimu:
        return 112.0
    if character == God_Reimu:
        return 132.0
    if character == VodkAlice:
        return 112.0
    else:
        return 0

def getPosY_with_char(character):
    if character == Satanae:
        return 280.0
    if character == Reimu:
        return 270.0
    if character == God_Reimu:
        return 270.0
    if character == VodkAlice:
        return 280.0
    else:
        return 0

def convert_face_into_ID(face):
    exp_names = ["no", "n2", "dp", "an", "sw", "hp", "pr", "sp"]
    if face == "not found":
        return face
    if face == "end":
        return 8
    for x in range(len(exp_names)):
        if face == exp_names[x]:
            face = x
            return face


def generate_code(character_name, input_pos_x, input_pos_Y, face):
    timelabel = 0
    playerShow = 1
    bossShow = 1
    dialogType = 0
    first_dialogue = 1
    for line_number in range(len(character_name)):
        character = is_character_player(character_name, line_number)
        bubbleType = 0  # get_bubble_Type()
        if character != 0:
            if character == -1: #a dialogType Label has been detected, meaning there's a new dialogue
                if first_dialogue != 1:
                    generate_end_code(dialogType, timelabel)
                first_dialogue = 0
                dialogType = getDialogType(character_name, line_number)
                timelabel = 0
                playerShow = 1
                bossShow = 1
                timelabel = generate_code_on_top(dialogType, input_pos_x, input_pos_Y, timelabel)
            else:
                if character != 10:
                    pos_X = getPosX_with_char(character)
                    pos_Y = getPosY_with_char(character)
                    timelabel = generate_code_for_player_char(playerShow, timelabel, pos_X, pos_Y, bubbleType, face[line_number])
                    playerShow = 0
                else:
                    timelabel = generate_code_for_boss_char(bossShow, timelabel, input_pos_x, input_pos_Y, bubbleType, face[line_number])
                    bossShow = 0
    generate_end_code(dialogType, timelabel)



def getDialogType(character_name, line_number):
    DialogType = 0
    if character_name[line_number] == 'b':
        DialogType = 0
    if character_name[line_number] == 'e':
        DialogType = 1
    if character_name[line_number] == 'X':
        DialogType = 2
    return DialogType


def generate_end_code(dialogType, timelabel):
    if dialogType == 0:
        print("""playerHide();
bossHide(0);
textboxHide();
skippable(0);
+30: //""", timelabel+30,"""
end();
    """)
    if dialogType == 1:
        print("""playerHide();
bossHide(0);
textboxHide();
skippable(0);
+1: // """, timelabel+1,"""
stageEnd();
musicEnd();
skippable(0);
+30: // """, timelabel+31,"""
end();  
    """)
    if dialogType == 2:
        print("""playerHide();
bossHide(0);
textboxHide();
skippable(0);
+1: // """, timelabel + 1, """
stageEnd();
musicEnd();
skippable(0);
+30: // """, timelabel + 31, """
end();
        """)


def generate_code_on_top(dialogType, input_pos_x, input_pos_Y, timelabel):
    if dialogType == 1:
        print("""
            
    //ending dialogue    
    
skippable(0);
playerShow(0);
bossShow(0);
bossFace(8, 0);
+4: // """, timelabel+4 ,"""
bossFace(8, 0);
speakerBoss(0);
bubblePos(""", input_pos_x, "," , input_pos_Y, """);
+30: // """, timelabel+34)
        timelabel += 34
    if dialogType == 0:
        print("// begin dialogue")
    if dialogType == 2:
        print("// special dialogue")
    return timelabel

def generate_code_for_player_char(playerShow, timelabel, pos_X, pos_Y, bubbleType, face):
    faceId = convert_face_into_ID(face)
    print("playerFace(", faceId, "); //", face);
    if playerShow == 1:
        print("playerShow(0);")
    print("speakerPlayer();")
    print("bubbleType(", bubbleType, ");")
    print("bubblePos(", pos_X, ",", pos_Y, ");")
    print("""textAdd("");
textAdd("");""")
    timelabel += 4
    print("+4: //", timelabel)
    print("textPause(600);")
    timelabel += 4
    print("+4: //", timelabel)
    return timelabel


def generate_code_for_boss_char(bossShow, timelabel, pos_X, pos_Y, bubbleType, face):
    faceId = convert_face_into_ID(face)
    print("bossFace(", faceId, ", 0); //", face);
    if bossShow == 1:
        print("bossShow(0);")
    print("speakerBoss(0);")
    print("bubbleType(", bubbleType, ");")
    print("bubblePos(", pos_X, ",", pos_Y, ");")
    print("""textAdd("");
textAdd("");""")
    timelabel += 4
    print("+4: //", timelabel)
    print("textPause(600);")
    timelabel += 4
    print("+4: //", timelabel)
    return timelabel

def getFace_in_line(line):
    x = 0
    expression = ""
    while line[x] != "{":
        x = x + 1
        if x >= len(line):
            expression = "not found"
            return expression
    x = x + 1
    while line[x] != "}":
        expression = expression+line[x]
        x = x + 1
    return expression

def main():
    line_number = 0
    face = []
    character_name = []
    filename = input("Filename: ")
    input_pos_x = float(input("Boss bubble pos X ?"))
    input_pos_y = float(input("Boss bubble pos Y ?"))
    
    with open(filename, 'r', 1, 'UTF-8') as file:
        text = file.readlines()
        for line in text:
            character_name.append(getCharacter_Name_in_line(line, character_name, face))
            face.append(getFace_in_line(line))
        generate_code(character_name, input_pos_x, input_pos_y, face)

def getCharacter_Name_in_line(line, character_name, face):
    name = ""
    x = 0
    character_name = ""
    print(line)
    if x+1 < len(line):
        if line[0] != "[":
            while line[x] != ":":
                name = name + line[x]
                x = x + 1
            for y in range(x):
                if y == x - 1:
                    character_name = character_name + name
            return character_name
        character_name = line[1]
        return character_name



main()