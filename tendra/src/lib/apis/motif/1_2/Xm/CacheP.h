/*
    COPYRIGHT NOTICE

    This program is the proprietary property of IXI Ltd, a subsidiary
    of the Santa Cruz Operation (SCO). Use, reproduction, production
    of amended versions and/or transfer of this program is permitted
    PROVIDED THAT:

    (a)  This legend be preserved on any such reproduction and amended
         version.

    (b)  Any recipient of such reproduction or amended version accept
         the conditions set out in this legend.

    IXI accepts no liability whatsoever in relation to any use to
    which this program may be put and gives no warranty as to the
    program's suitability for any purpose.

    All rights reserved.

    Copyright (c) 1995, 1996

*/


/* SCO CID (IXI) CacheP.h,v 1.1 1996/08/08 14:12:16 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/GadgetP.h";

+DEFINE DataToGadgetCache(p) %% ((char *)p - XtOffsetOf(XmGadgetCacheRef, data)) %%;

+DEFINE ClassCacheHead(cp) %% ((cp)->cache_head) %%;
+DEFINE ClassCacheCopy(cp) %% ((cp)->cache_copy) %%;
+DEFINE ClassCacheCompare(cp) %% ((cp)->cache_compare) %%;
+DEFINE CacheDataPtr(cp) %% ((XtPointer)&((XmGadgetCacheRef*)p)-> data) %%;

+FUNC void _XmCacheDelete( XtPointer );
+FUNC void _XmCacheCopy( XtPointer, XtPointer, size_t);
+FUNC XtPointer _XmCachePart(XmCacheClassPartPtr, XtPointer, size_t);

