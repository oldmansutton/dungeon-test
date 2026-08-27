// moreau.h
//
// Copyright (c) 2026 - oldmansutton
//

#ifndef MOREAU_H
#define MOREAU_H

#include "attributes.h"
#include "neural.h"

typedef enum {
    GENE_BODY_MASS,
    GENE_BODY_SIZE,
    GENE_BODY_DENSITY,
    GENE_METABOLISM,
    GENE_REFLEX,
    GENE_HARDINESS,
    GENE_COUNT
} Gene_Type;

typedef struct {
    float genes[GENE_COUNT];
    NN_Parameters neuralParameters;
} Genome;

#endif
