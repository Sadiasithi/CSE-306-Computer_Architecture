#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back

const ll INSTRUCTION_SIZE=1;

const string ZERO="0000";
const string T0="0001";
const string T1="0010";
const string T2="0011";
const string T3="0100";
const string T4="0101";
const string SP="0110";

//PHALCNBIOFKEMGDJ
// j, ori, add, lw, sub, beq, addi, sll, bneq, andi, nor, and, sw, or, subi, srl

// const string J="0000";
// const string ORI="0001";
// const string ADD="0010";
// const string LW="0011";
// const string SUB="0100";
// const string BEQ="0101";
// const string ADDI="0110";
// const string SLL="0111";
// const string BNEQ="1000";
// const string ANDI="1001";
// const string NOR="1010";
// const string AND="1011";
// const string SW="1100";
// const string OR="1101";
// const string SUBI="1110";
// const string SRL="1111";


const string OR="0000";
const string ADD="0001";
const string J="0010";
const string BNEQ="0011";
const string SW="0100";
const string BEQ="0101";
const string SUBI="0110";
const string LW="0111";
const string SRL="1000";
const string NOR="1001";
const string ORI="1010";
const string SUB="1011";
const string ANDI="1100";
const string AND="1101";
const string SLL="1110";
const string ADDI="1111";

const bool isSPEnabled=true;
const string enableSP="addi $sp, $zero, 15";

void processLine(string s);
void processPushPop(string s,ll type,string reg);

ll lineCount;
map<string,ll>labelAddress;
vector<string>instructionList,lineList;

vector<string> splitString(string s){
    vector<string>splitedString;
    string stringPart="";

    for(ll i=0;i<s.size();i++){
        if(s[i]==' ' || s[i]==',' || s[i]=='\t'){
            if(stringPart!=""){
                splitedString.pb(stringPart);
                stringPart="";
            }
        }
        else stringPart+=s[i];
    }
    if(stringPart!="") splitedString.pb(stringPart);
    return splitedString;
}

void getLabel(string s){
    vector<string> splitedString=splitString(s);
    string part=splitedString[0];

    if(part=="sub"||part=="ori" ||part=="bneq"||part=="addi"||
       part=="beq"||part=="or"  ||part=="sw"  ||part=="srl" ||
       part=="and"||part=="andi"||part=="lw"  ||part=="add" ||
       part=="sll"||part=="subi"||part=="j"   ||part=="nor"){}
    else if( part=="push" || part=="pop"){lineCount++;}
    else{
       part.pop_back();
       labelAddress[part]=lineCount;
    }
}

string getInstructionCode(string s){
    if(s=="sub") return SUB;
    else if(s=="ori") return ORI;
    else if(s=="bneq") return BNEQ;
    else if(s=="addi") return ADDI;
    else if(s=="beq") return BEQ;
    else if(s=="or") return OR;
    else if(s=="sw") return SW;
    else if(s=="srl") return SRL;
    else if(s=="and") return AND;
    else if(s=="andi") return ANDI;
    else if(s=="lw") return LW;
    else if(s=="add") return ADD;
    else if(s=="sll") return SLL;
    else if(s=="subi") return SUBI;
    else if(s=="j") return J;
    else if(s=="nor") return NOR;
    else return "";
}


string getRegisterCode(string s){
    if (s=="$t0") return T0;
    else if (s=="$t1") return T1;
    else if (s=="$t2") return T2;
    else if (s=="$t3") return T3;
    else if (s=="$t4") return T4;
    else if (s=="$zero") return ZERO;
    else if (s=="$sp") return SP;
    else return "";
}

void processPushPop(string s,ll type,string reg){
    if(type==0){
        processLine("sw "+reg+", 0($sp)");
        processLine("subi $sp, $sp, 1");
    }
    else if(type==1){
        processLine("addi $sp, $sp, 1");
        processLine("lw "+reg+", 0($sp))");
    }
    lineCount++;
}

void processLine(string s){
    cout<<s<<endl;
    vector<string> splitedString=splitString(s);
    string part=splitedString[0];
    string processedString="";

    // cout<<splitedString.size()<<endl;
    // for(auto it: splitedString){
    //     cout<<it<<" ";
    // }
    // cout<<endl;

    processedString=getInstructionCode(part);

    if(processedString==""){
        if(part=="push"){ // 0->PUSH
            processPushPop(s,0,splitedString[1]);
            return;
        }
        else if(part=="pop"){ // 1->POP
            processPushPop(s,1,splitedString[1]);
            return;
        }
        else splitedString.erase(splitedString.begin());

        part=splitedString[0];
        processedString=getInstructionCode(part);
    }

    // R format : sub, or, and, add, nor
    if(processedString==SUB || processedString==OR || processedString==AND || processedString==ADD || processedString==NOR){
        processedString+=getRegisterCode(splitedString[2]);
        processedString+=getRegisterCode(splitedString[3]);
        processedString+=getRegisterCode(splitedString[1]);
    }
    // S format : srl, sll
    else if(processedString==SRL || processedString==SLL){
        processedString+=getRegisterCode(splitedString[2]);
        processedString+=getRegisterCode(splitedString[1]);

        ll n=stoi(splitedString[3]);
        string bin=bitset<4>(n).to_string();
        processedString+=bin;
    }
    // I format constant : ori, addi, andi, subi
    else if(processedString==ORI || processedString==ADDI || processedString==ANDI || processedString==SUBI){
        processedString+=getRegisterCode(splitedString[2]);
        processedString+=getRegisterCode(splitedString[1]);

        ll n=stoi(splitedString[3]);
        string bin=bitset<4>(n).to_string();
        processedString+=bin;
    }
     // I format control : beq, bneq
    else if(processedString==BEQ || processedString==BNEQ){
        processedString+=getRegisterCode(splitedString[2]);
        processedString+=getRegisterCode(splitedString[1]);

        ll n=labelAddress[splitedString[3]];
        n=(n-lineCount-1)*INSTRUCTION_SIZE;
        string bin=bitset<4>(n).to_string();

        processedString+=bin;
    }
    // I format memory : sw, lw
    else if(processedString==SW || processedString==LW){
        string tmp;
        stringstream str(splitedString[2]);
        if(getline(str,part,'(')) tmp=part;
        if(getline(str,part,')')) {processedString+=getRegisterCode(part);cout<<1<<" "<<part<<endl;}
        processedString+=getRegisterCode(splitedString[1]);
        cout<<2<<" "<<splitedString[1]<<endl;

        ll n=stoi(tmp)*INSTRUCTION_SIZE;
        string bin=bitset<4>(n).to_string();

        processedString+=bin;
    }
    // J format : j
    else if(processedString==J){
        ll n=labelAddress[splitedString[1]]; cout<<n<<endl;
        n=n*INSTRUCTION_SIZE;
        string bin=bitset<8>(n).to_string();

        processedString+=bin;
        processedString+="0000";
    }
    lineList.pb(s);
    instructionList.pb(processedString);
}

string spacedBinPrint(string s){
    ll ind=0;
    string res;
    for(auto it: s){
        res+=it;
        ind++;
        if(ind%4==0) res+=" ";
    }
    return res;
}

string binToHex(string s){
    ll ind=0,n;
    string tmp="",res="";

    for(auto it: s){
        tmp+=it;
        ind++;
        if(ind%4==0){
            if(tmp=="0000") res+="0";
            else  if(tmp=="0001") res+="1";
            else  if(tmp=="0010") res+="2";
            else  if(tmp=="0011") res+="3";
            else  if(tmp=="0100") res+="4";
            else  if(tmp=="0101") res+="5";
            else  if(tmp=="0110") res+="6";
            else  if(tmp=="0111") res+="7";
            else  if(tmp=="1000") res+="8";
            else  if(tmp=="1001") res+="9";
            else  if(tmp=="1010") res+="A";
            else  if(tmp=="1011") res+="B";
            else  if(tmp=="1100") res+="C";
            else  if(tmp=="1101") res+="D";
            else  if(tmp=="1110") res+="E";
            else  if(tmp=="1111") res+="F";
            tmp="";
        }
    }
    return res;
}

int main(){
    ifstream fin ("assembly_text.txt");
    ofstream foutbin ("machine_code.bin");
    ofstream fouthex ("machine_code.hex");
    string s;

    if(fin.is_open()){
        fouthex<<"v2.0 raw"<<endl;
        lineCount=0;
        if(isSPEnabled) lineCount++;
        while(getline(fin,s)){
            getLabel(s);
            lineCount++;
            cout<<lineCount<<endl;
            if(s=="end:") break;
        }
        fin.close();
        for(auto it:labelAddress){
            cout<<it.first<<" "<<it.second<<endl;
        }

        fin.open("assembly_text.txt");
        lineCount=0;
        if(isSPEnabled){
            s=enableSP;
            processLine(s);
            // foutbin<<spacedBinPrint(instruction)<<" : "<<s<<endl;
            // fouthex<<binToHex(instruction)<<endl;
            lineCount++;
        }
        while(getline(fin,s)){
            if(s=="end:") break;
            processLine(s);
            // foutbin<<spacedBinPrint(instruction)<<" : "<<s<<endl;
            // fouthex<<binToHex(instruction)<<endl;
            lineCount++;
        }
        for(ll i=0;i<instructionList.size();i++){
            foutbin<<spacedBinPrint(instructionList[i])<<" : "<<lineList[i]<<endl;
            fouthex<<binToHex(instructionList[i])<<endl;
        }
        fouthex<<"0000"<<endl;
        fin.close();
    }
    else cout<<"Unable to open file"<<endl;
    foutbin.close();
    fouthex.close();
}
