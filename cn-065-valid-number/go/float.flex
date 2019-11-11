%{
    package main
%}

WHITE   " "|\t|\f|\r|\v
%%
{WHITE}*[+-]?(([0-9]+(\.[0-9]*)?)|(\.[0-9]+))([Ee][+-]?[0-9]+)?{WHITE}* {return true;}
. {return false;}
%%

func main() {
    
}
