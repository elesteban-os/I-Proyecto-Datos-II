class Card {
    char *image;

    char getImage(){
        return *image;
    }

    char setImage(char *info){
        image = info;
    }
};