include (diamond_support.pri)

# Input
HEADERS += src/DiamondBuildPrompter.h \
           src/DiamondBuildTask.h \
           src/DiamondBuildWorker.h \
           src/DiamondBuildWorkerFactory.h \
           src/DiamondClassifyPrompter.h \
           src/DiamondClassifyTask.h \
           src/DiamondClassifyWorker.h \
           src/DiamondClassifyWorkerFactory.h \
           src/DiamondSupport.h \
           src/DiamondSupportPlugin.h \
           src/DiamondTaxonomyDataValidator.h \
           src/GenomesPreparationTask.h

SOURCES += src/DiamondBuildPrompter.cpp \
           src/DiamondBuildTask.cpp \
           src/DiamondBuildWorker.cpp \
           src/DiamondBuildWorkerFactory.cpp \
           src/DiamondClassifyPrompter.cpp \
           src/DiamondClassifyTask.cpp \
           src/DiamondClassifyWorker.cpp \
           src/DiamondClassifyWorkerFactory.cpp \
           src/DiamondSupport.cpp \
           src/DiamondSupportPlugin.cpp \
           src/DiamondTaxonomyDataValidator.cpp \
           src/GenomesPreparationTask.cpp

TRANSLATIONS += transl/english.ts transl/russian.ts
