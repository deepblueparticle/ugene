include (U2Formats.pri)

# Input
HEADERS += src/ABIFormat.h \
           src/AbstractVariationFormat.h \
           src/ASNFormat.h \
           src/BAMUtils.h \
           src/BedFormat.h \
           src/ClustalWAlnFormat.h \
           src/ColumnDataParser.h \
           src/Database.h \
           src/DatabaseConnectionFormat.h \
           src/DifferentialFormat.h \
           src/DNAQualityIOUtils.h \
           src/DocumentFormatUtils.h \
           src/EMBLGenbankAbstractDocument.h \
           src/EMBLPlainTextFormat.h \
           src/FastaFormat.h \
           src/FastqFormat.h \
           src/FpkmTrackingFormat.h \
           src/GenbankLocationParser.h \
           src/GenbankPlainTextFormat.h \
           src/GFFFormat.h \
           src/GTFFormat.h \
           src/IOLibUtils.h \
           src/MegaFormat.h \
           src/MSFFormat.h \
           src/NewickFormat.h \
           src/NEXUSFormat.h \
           src/NEXUSParser.h \
           src/PDBFormat.h \
           src/PDWFormat.h \
           src/PhylipFormat.h \
           src/PlainTextFormat.h \
           src/RawDNASequenceFormat.h \
           src/SAMFormat.h \
           src/SCFFormat.h \
           src/SNPDatabaseUtils.h \
           src/SimpleSNPVariationFormat.h \
           src/StdResidueDictionary.h \
           src/StockholmFormat.h \
           src/StreamSequenceReader.h \
           src/StreamSequenceWriter.h \
           src/SwissProtPlainTextFormat.h \
           src/VCF4VariationFormat.h \
           src/VectorNtiSequenceFormat.h \
           src/ace/AceFormat.h \
           src/ace/AceImportUtils.h \
           src/ace/AceImporter.h \
           src/ace/CloneAssemblyWithReferenceToDbiTask.h \
           src/ace/ConvertAceToSqliteTask.h \
           src/mysql_dbi/MysqlAssemblyDbi.h \
           src/mysql_dbi/MysqlAttributeDbi.h \
           src/mysql_dbi/MysqlBlobInputStream.h \
           src/mysql_dbi/MysqlBlobOutputStream.h \
           src/mysql_dbi/MysqlCrossDatabaseReferenceDbi.h \
           src/mysql_dbi/MysqlDbi.h \
           src/mysql_dbi/MysqlFeatureDbi.h \
           src/mysql_dbi/MysqlModDbi.h \
           src/mysql_dbi/MysqlMsaDbi.h \
           src/mysql_dbi/MysqlObjectDbi.h \
           src/mysql_dbi/MysqlObjectRelationsDbi.h \
           src/mysql_dbi/MysqlSequenceDbi.h \
           src/mysql_dbi/MysqlUdrDbi.h \
           src/mysql_dbi/MysqlVariantDbi.h \
           src/mysql_dbi/util/MysqlAssemblyAdapter.h \
           src/mysql_dbi/util/MysqlAssemblyUtils.h \
           src/mysql_dbi/util/MysqlDbiUtils.h \
           src/mysql_dbi/util/MysqlHelpers.h \
           src/mysql_dbi/util/MysqlModificationAction.h \
           src/mysql_dbi/util/MysqlMultiTableAssemblyAdapter.h \
           src/mysql_dbi/util/MysqlSingleTableAssemblyAdapter.h \
           src/mysql_dbi/util/upgraders/MysqlUpgrader.h \
           src/mysql_dbi/util/upgraders/MysqlUpgraderFrom_1_14_To_1_15.h \
           src/mysql_dbi/util/upgraders/MysqlUpgraderFrom_1_15_To_1_16.h \
           src/mysql_dbi/util/upgraders/MysqlUpgraderFrom_1_16_To_1_17.h \
           src/mysql_dbi/util/upgraders/MysqlUpgraderFrom_1_16_To_1_24.h \
           src/sqlite_dbi/SQLiteAssemblyDbi.h \
           src/sqlite_dbi/SQLiteAttributeDbi.h \
           src/sqlite_dbi/SQLiteBlobInputStream.h \
           src/sqlite_dbi/SQLiteBlobOutputStream.h \
           src/sqlite_dbi/SQLiteDbi.h \
           src/sqlite_dbi/SQLiteFeatureDbi.h \
           src/sqlite_dbi/SQLiteModDbi.h \
           src/sqlite_dbi/SQLiteMsaDbi.h \
           src/sqlite_dbi/SQLiteObjectDbi.h \
           src/sqlite_dbi/SQLiteObjectRelationsDbi.h \
           src/sqlite_dbi/SQLiteSequenceDbi.h \
           src/sqlite_dbi/SQLiteUdrDbi.h \
           src/sqlite_dbi/SQLiteVariantDbi.h \
           src/sqlite_dbi/assembly/MultiTableAssemblyAdapter.h \
           src/sqlite_dbi/assembly/RTreeAssemblyAdapter.h \
           src/sqlite_dbi/assembly/SingleTableAssemblyAdapter.h \
           src/sqlite_dbi/util/SqliteUpgrader.h \
           src/sqlite_dbi/util/SqliteUpgraderFrom_0_To_1_13.cpp \
           src/tasks/BgzipTask.h \
           src/tasks/ConvertAssemblyToSamTask.h \
           src/tasks/ConvertFileTask.h \
           src/tasks/ConvertSnpeffVariationsToAnnotationsTask.h \
           src/tasks/MergeBamTask.h \
           src/tasks/MysqlUpgradeTask.h \
           src/util/AssemblyAdapter.h \
           src/util/AssemblyPackAlgorithm.h \
           src/util/SnpeffInfoParser.h

SOURCES += src/ABIFormat.cpp \
           src/AbstractVariationFormat.cpp \
           src/ASNFormat.cpp \
           src/BAMUtils.cpp \
           src/BedFormat.cpp \
           src/ClustalWAlnFormat.cpp \
           src/ColumnDataParser.cpp \
           src/Database.cpp \
           src/DatabaseConnectionFormat.cpp \
           src/DifferentialFormat.cpp \
           src/DNAQualityIOUtils.cpp \
           src/DocumentFormatUtils.cpp \
           src/EMBLGenbankAbstractDocument.cpp \
           src/EMBLPlainTextFormat.cpp \
           src/FastaFormat.cpp \
           src/FastqFormat.cpp \
           src/FpkmTrackingFormat.cpp \
           src/GenbankLocationParser.cpp \
           src/GenbankPlainTextFormat.cpp \
           src/GFFFormat.cpp \
           src/GTFFormat.cpp \
           src/MegaFormat.cpp \
           src/MSFFormat.cpp \
           src/NewickFormat.cpp \
           src/NEXUSFormat.cpp \
           src/PDBFormat.cpp \
           src/PDWFormat.cpp \
           src/PhylipFormat.cpp \
           src/PlainTextFormat.cpp \
           src/RawDNASequenceFormat.cpp \
           src/SAMFormat.cpp \
           src/SCFFormat.cpp \
           src/SimpleSNPVariationFormat.cpp \
           src/SNPDatabaseUtils.cpp \
           src/StdResidueDictionary.cpp \
           src/StockholmFormat.cpp \
           src/StreamSequenceReader.cpp \
           src/StreamSequenceWriter.cpp \
           src/SwissProtPlainTextFormat.cpp \
           src/VCF4VariationFormat.cpp \
           src/VectorNtiSequenceFormat.cpp \
           src/ace/AceFormat.cpp \
           src/ace/AceImporter.cpp \
           src/ace/AceImportUtils.cpp \
           src/ace/CloneAssemblyWithReferenceToDbiTask.cpp \
           src/ace/ConvertAceToSqliteTask.cpp \
           src/mysql_dbi/MysqlAssemblyDbi.cpp \
           src/mysql_dbi/MysqlAttributeDbi.cpp \
           src/mysql_dbi/MysqlBlobInputStream.cpp \
           src/mysql_dbi/MysqlBlobOutputStream.cpp \
           src/mysql_dbi/MysqlCrossDatabaseReferenceDbi.cpp \
           src/mysql_dbi/MysqlDbi.cpp \
           src/mysql_dbi/MysqlFeatureDbi.cpp \
           src/mysql_dbi/MysqlModDbi.cpp \
           src/mysql_dbi/MysqlMsaDbi.cpp \
           src/mysql_dbi/MysqlObjectDbi.cpp \
           src/mysql_dbi/MysqlObjectRelationsDbi.cpp \
           src/mysql_dbi/MysqlSequenceDbi.cpp \
           src/mysql_dbi/MysqlUdrDbi.cpp \
           src/mysql_dbi/MysqlVariantDbi.cpp \
           src/mysql_dbi/util/MysqlAssemblyAdapter.cpp \
           src/mysql_dbi/util/MysqlAssemblyUtils.cpp \
           src/mysql_dbi/util/MysqlDbiUtils.cpp \
           src/mysql_dbi/util/MysqlHelpers.cpp \
           src/mysql_dbi/util/MysqlModificationAction.cpp \
           src/mysql_dbi/util/MysqlMultiTableAssemblyAdapter.cpp \
           src/mysql_dbi/util/MysqlSingleTableAssemblyAdapter.cpp \
           src/mysql_dbi/util/upgraders/MysqlUpgrader.cpp \
           src/mysql_dbi/util/upgraders/MysqlUpgraderFrom_1_14_To_1_15.cpp \
           src/mysql_dbi/util/upgraders/MysqlUpgraderFrom_1_15_To_1_16.cpp \
           src/mysql_dbi/util/upgraders/MysqlUpgraderFrom_1_16_To_1_17.cpp \
           src/mysql_dbi/util/upgraders/MysqlUpgraderFrom_1_16_To_1_24.cpp \
           src/sqlite_dbi/SQLiteAssemblyDbi.cpp \
           src/sqlite_dbi/SQLiteAttributeDbi.cpp \
           src/sqlite_dbi/SQLiteBlobInputStream.cpp \
           src/sqlite_dbi/SQLiteBlobOutputStream.cpp \
           src/sqlite_dbi/SQLiteDbi.cpp \
           src/sqlite_dbi/SQLiteFeatureDbi.cpp \
           src/sqlite_dbi/SQLiteModDbi.cpp \
           src/sqlite_dbi/SQLiteMsaDbi.cpp \
           src/sqlite_dbi/SQLiteObjectDbi.cpp \
           src/sqlite_dbi/SQLiteObjectRelationsDbi.cpp \
           src/sqlite_dbi/SQLiteSequenceDbi.cpp \
           src/sqlite_dbi/SQLiteUdrDbi.cpp \
           src/sqlite_dbi/SQLiteVariantDbi.cpp \
           src/sqlite_dbi/assembly/MultiTableAssemblyAdapter.cpp \
           src/sqlite_dbi/assembly/RTreeAssemblyAdapter.cpp \
           src/sqlite_dbi/assembly/SingleTableAssemblyAdapter.cpp \
           src/sqlite_dbi/util/SqliteUpgrader.cpp \
           src/sqlite_dbi/util/SqliteUpgraderFrom_0_To_1_13.cpp \
           src/tasks/BgzipTask.cpp \
           src/tasks/ConvertAssemblyToSamTask.cpp \
           src/tasks/ConvertFileTask.cpp \
           src/tasks/ConvertSnpeffVariationsToAnnotationsTask.cpp \
           src/tasks/MergeBamTask.cpp \
           src/tasks/MysqlUpgradeTask.cpp \
           src/util/AssemblyPackAlgorithm.cpp \
           src/util/SnpeffInfoParser.cpp

RESOURCES += U2Formats.qrc
TRANSLATIONS += transl/english.ts \
                transl/russian.ts
