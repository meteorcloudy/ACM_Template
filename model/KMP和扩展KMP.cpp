//KMP

// nex[i] = max{z | b[i-z+1 ~ i] = b[0 ~ z-1]}
// ex[i] = max{z | a[i-z+1 ~ i] = b[0 ~ z-1]}

void KMP(){
    int lena = strlen(a) , lenb = strlen(b) ;
    nex[0] = 0 ;
    int j = 0 ;
    for (int i = 1 ; i < lenb ; i++){
        while (j && b[j]!=b[i]) j = nex[j-1];
        if (b[i]==b[j]) ++j;
        nex[i] = j ;
    }

    j = 0 ;
    for (int i = 0 ; i < lena ; i++){
        while (j && b[j]!=a[i]) j = nex[j-1] ;
        if (a[i]==b[j]) ++j;
        ex[i] = j ;
    }
}

//KMP

// nex[i] = max{z | b[i ~ i+z-1] = b[0 ~ z-1]}
// ex[i] = max{z | a[i ~ i+z-1] = b[0 ~ z-1]}

void KMP2(){
    int lena = strlen(a) , lenb = strlen(b) ;
    nex[0] = lenb ; nex[1] = lenb - 1 ;
    for (int i = 0 ; i < lenb-1 ; i++)
        if (b[i] != b[i+1]){
            nex[1] = i ;
            break ;
        }
    int j , k = 1 , p , L ;
    for (int i = 2 ; i < lenb ; i++){
        p = k + nex[k] -1 ; L = nex[i-k] ;
        if (i + L <= p) nex[i] = L ;
        else{
            j = p - i + 1 ;
            if (j < 0) j = 0 ;
            while (i+j < lenb && b[i+j]==b[j]) j++;
            nex[i] = j ; k = i ;
        }
    }

    int len = min(lena , lenb) ; ex[0] = len ;
    for (int i = 0 ; i < len ; i++)
        if (a[i] != b[i]){
            ex[0] = i ;
            break ;
        }
    k = 0 ;
    for (int i = 1 ; i < lena ; i++){
        int p = k + ex[k] - 1 ; L = nex[i-k] ;
        if (i + L <= p) ex[i] = L ;
        else{
            j = p - i + 1 ;
            if (j < 0) j = 0 ;
            while (i+j<lena && j<lenb && a[i+j]==b[j]) j++;
            ex[i] = j ; k = i ;
        }
    }
}
