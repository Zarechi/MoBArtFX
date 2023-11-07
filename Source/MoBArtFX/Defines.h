#pragma once

#define kPRINT_ARGS(index, time, color, text)	GEngine->AddOnScreenDebugMessage( index, time, color, text )
//  Print a white screen debug text for a tick
#define kPRINT_TICK(text)						kPRINT_ARGS( INDEX_NONE, 0.0f, FColor::White, text )
//  Print a white screen debug text for 5.0s
#define kPRINT(text)							kPRINT_ARGS( INDEX_NONE, 5.0f, FColor::White, text )
//  Print a red screen debug error text for 5.0s
#define kPRINT_ERROR(text)						kPRINT_ARGS( INDEX_NONE, 5.0f, FColor::Red, FString( "ERROR : " ) + FString( text ) )
//  Print a yellow sreen debug warning text for 5.0s
#define kPRINT_WARNING(text)                    kPRINT_ARGS( INDEX_NONE, 5.0f, FColor::Yellow, FString( "WARNING: " ) + FString( text ) )