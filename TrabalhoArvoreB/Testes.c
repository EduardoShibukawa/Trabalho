void ExibeBTPage (BTPage p, int RRN) {
    printf("RRN %d \n", RRN);
    printf("Numero de chaves %d \n", p.numeroChaves);
    printf("Deleted %d \n", p.Deleted);
    printf("Chaves %d %d %d %d \n", p.registro[0].chave, p.registro[1].chave, p.registro[2].chave, p.registro[3].chave);
    printf("Offset %d %d %d %d \n", p.registro[0].byteOffSet, p.registro[1].byteOffSet, p.registro[2].byteOffSet, p.registro[3].byteOffSet);
    printf("Filhos %d %d %d %d %d \n", p.child[0], p.child[1], p.child[2], p.child[3], p.child[4]);
}
void Testar () {
    BTPage p;
    Registro reg;
    int i=1;
    /*
    AtualizarCabecalho(1);
    InicializarBTPage(&p);
    SalvarPagina(&p, AchaRRNRaiz());
    SalvarPagina(&p, AcharRRNDisponivel());
    SalvarPagina(&p, AcharRRNDisponivel());
    SalvarPagina(&p, AcharRRNDisponivel());
    SalvarPagina(&p, AcharRRNDisponivel());
    SalvarPagina(&p, AcharRRNDisponivel());
    SalvarPagina(&p, AcharRRNDisponivel());
    */
    for (i=1; i<=14; i++) {
        reg.byteOffSet = i;
        reg.chave = i;
        Insercao(reg);
    }
    /*
    reg.byteOffSet = i;
    reg.chave = 33;
    Insercao(reg);
    reg.byteOffSet = i;
    reg.chave = 42;
    Insercao(reg);
    reg.byteOffSet = i;
    reg.chave = 13;
    Insercao(reg);
    reg.byteOffSet = i;
    reg.chave = 18;
    Insercao(reg);

    reg.byteOffSet = i;
    reg.chave = 89;
    Insercao(reg);

    reg.byteOffSet = i;
    reg.chave = 11;
    Insercao(reg);

    reg.byteOffSet = i;
    reg.chave = 1;
    Insercao(reg);

    reg.byteOffSet = i;
    reg.chave = 73;
    Insercao(reg);        reg.byteOffSet = i;
    reg.chave = 72;
    Insercao(reg);        reg.byteOffSet = i;
    reg.chave = 1;
    Insercao(reg);
    reg.byteOffSet = i;
    reg.chave = 7;
    Insercao(reg);
    reg.byteOffSet = i;
    reg.chave = 8;
    Insercao(reg);
    reg.byteOffSet = i;
    reg.chave = 1;
    Insercao(reg);
    reg.byteOffSet = i;
    reg.chave = 1;
    Insercao(reg);

    */
    for (i = 1; i <= 12; i++) {
        ExibeBTPage(*CarregaPagina(i), i);
    }
    ExibeBTPage(*CarregaPagina(AchaRRNRaiz()), AchaRRNRaiz());
}
