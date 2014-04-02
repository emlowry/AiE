import AIE
import Geometry
import game
import math

#This is just a simple Level Grid that sets up a grid based level that fills the entire screen
#this level is static in that is is the size of the viewport and no larger should you wish to create a 
#level that can be larger than the screen bounds then modify away.
#Tiles in the level can be turned off and on by a simple click of the left mouse button

class LevelGrid:
	def __init__(self, screenProperties, tileSize ):
		self.tileSize = tileSize
		self.buttonPressed = False
		self.levelWidth = math.ceil(screenProperties['width']/ tileSize['width'])
		self.levelHeight= math.ceil(screenProperties['height']/ tileSize['height'])
		self.levelSize = self.levelWidth * (self.levelHeight+1)
		print "LevelSize :", self.levelWidth, " ", self.levelHeight
		self.levelTiles = [None] * int(self.levelSize)
		self.observers = ObserverList()
		
		for i in range(int(self.levelSize)):
			self.levelTiles[i] = Tile()
			self.levelTiles[i].x = self.tileSize['width'] * (i % int(self.levelWidth))
			self.levelTiles[i].y = self.tileSize['height'] * ( (int(i)/(int(self.levelWidth))))
	
	def loadSprites(self):
		#load all sprites for each tile
		for i in range(int(self.levelSize)):
			spriteID = AIE.CreateSprite( self.levelTiles[i].getImageName(), self.tileSize['width'], self.tileSize['height'], 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0xff, 0xff, 0xff, 0xff )
			self.levelTiles[i].setSpriteID(spriteID)
			spriteID = AIE.CreateSprite( self.levelTiles[i].getOtherImageName(), self.tileSize['width'], self.tileSize['height'], 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0xff, 0xff, 0xff, 0xff )
			self.levelTiles[i].setOtherSpriteID(spriteID)
			#Move Tile to appropriate location
			AIE.MoveSprite( self.levelTiles[i].getSpriteID(), self.levelTiles[i].x, self.levelTiles[i].y )
			AIE.MoveSprite( self.levelTiles[i].getOtherSpriteID(), self.levelTiles[i].x, self.levelTiles[i].y )

	def register( self, observer, notification ):
		self.observers.add( observer, notification )

	def deregister( self, observer, notification ):
		self.observers.remove( observer, notification )
	
	def update(self, fDeltaTime):
		mouseX, mouseY = AIE.GetMouseLocation()
		
		if( AIE.GetMouseButton(0)  and (self.buttonPressed is False) ):
			self.buttonPressed = True
			tileIndex = int(self.resolveGridSquare(mouseX, mouseY))
			if( tileIndex >= 0 and tileIndex < self.levelSize ):
				self.levelTiles[tileIndex].setDraw()
				self.observers.notify( self )
				
		self.buttonPressed = not AIE.GetMouseButtonRelease(0)		
		
	def draw(self):
		for i in range( int(self.levelSize) ):
			if( self.levelTiles[i].shouldDraw() ):
				AIE.DrawSprite( self.levelTiles[i].getSpriteID() )
			else:
				AIE.DrawSprite( self.levelTiles[i].getOtherSpriteID() )

	def obstacleAt( self, xGrid, yGrid ):
		return( not self.levelTiles[ ( int(yGrid) * int(self.levelWidth) ) + int(xGrid) ].shouldDraw() )

	def toCorners( self, xGrid, yGrid ):
		xMin = xGrid * self.tileSize['width']
		yMin = yGrid * self.tileSize['height']
		return ( xMin, yMin, xMin + self.tileSize['width'], yMin + self.tileSize['height'] )

	def toGrid( self, xPixel, yPixel ):
		xGrid = math.floor(xPixel/self.tileSize['width'])
		yGrid = math.floor(yPixel/self.tileSize['height'])
		return ( xGrid, yGrid )

	def resolveGridSquare(self, xPos, yPos):
		xGridPos, yGridPos = self.toGrid( xPos, yPos )
		return (yGridPos * self.levelWidth) + xGridPos

	# Returns true if there are no obstacles between the given position and the
	# given target, excluding the grid squares of the position and target if
	# indicated
	def lineOfSight( self, xPos, yPos, xTarget, yTarget, bIgnorePosition, bIgnoreTarget ):
		xGridPos, yGridPos = self.toGrid( xPos, yPos )
		xGridTarget, yGridTarget = self.toGrid( xTarget, yTarget )
		if( ( xGridPos == xGridTarget and 1 >= math.fabs( yGridPos - yGridTarget ) ) or
			( yGridPos == yGridTarget and 1 >= math.fabs( xGridPos - xGridTarget ) ) ):
			return ( ( bIgnorePosition or not self.obstacleAt( xGridPos, yGridPos ) ) and
					 ( bIgnoreTarget or not self.obstacleAt( xGridTarget, yGridTarget ) ) )
		xMin = xGridPos if ( xGridPos < xGridTarget ) else xGridTarget
		yMin = yGridPos if ( yGridPos < yGridTarget ) else yGridTarget
		xMax = xGridPos if ( xGridPos > xGridTarget ) else xGridTarget
		yMax = yGridPos if ( yGridPos > yGridTarget ) else yGridTarget
		x = xMin
		y = yMin
		while( x <= xMax and y <= yMax ):
			if( ( not bIgnorePosition or x != xGridPos or y != yGridPos ) and
				( not bIgnoreTarget or x != xGridTarget or y != yGridTarget ) and
				self.obstacleAt( x, y ) ):
				return False
			corner1x, corner1y, corner2x, corner2y = self.toCorners( x + 1, y )
			if( Geometry.SegmentSquareIntersect( xPos, yPos, xTarget, yTarget, corner1x, corner1y, corner2x, corner2y ) ):
				x = x + 1
			else:
				corner1x, corner1y, corner2x, corner2y = self.toCorners( x, y + 1 )
				if( not Geometry.SegmentSquareIntersect( xPos, yPos, xTarget, yTarget, corner1x, corner1y, corner2x, corner2y ) ):
					x = x + 1
				y = y + 1
		return True
	
	def cleanUp(self):
		self.observers.clear()
		for i in range( int(self.levelSize) ):
			if( self.levelTiles[i].getSpriteID() != -1 ):
				AIE.DestroySprite( self.levelTiles[i].getSpriteID() )
			if( self.levelTiles[i].getOtherSpriteID() != -1 ):
				AIE.DestroySprite( self.levelTiles[i].getOtherSpriteID() )

#A simple tile class that is set up to control each individual tile in the game level
#each tile has a sprite ID and can be turned on or off to allow for tiles to be drawn or not.				
class Tile:
	def __init__(self):
		self.imageName = "./images/Red_Desert.jpg"
		self.otherImageName = "./images/crate_sideup.png"
		self.spriteID = -1
		self.otherSpriteID = -1
		self.bShouldDraw = True
		self.state = 0
		self.x = 0
		self.y = 0
	
	def getImageName(self):
		return self.imageName
	
	def getOtherImageName(self):
		return self.otherImageName
		
	def getState(self):
		return self.state
	
	def getSpriteID(self):
		return self.spriteID
		
	def setSpriteID(self, a_spriteID):
		self.spriteID = a_spriteID
	
	def getOtherSpriteID(self):
		return self.otherSpriteID
		
	def setOtherSpriteID(self, a_spriteID):
		self.otherSpriteID = a_spriteID
	
	def setDraw(self):
		self.bShouldDraw = not self.bShouldDraw
	
	def shouldDraw(self):
		return self.bShouldDraw

# Simple class for handling observers
class ObserverList:
	def __init__(self):
		self.observers = set()
		
	def add( self, observer, notification ):
		self.observers.add( ( observer, notification ) )
		
	def remove( self, observer, notification ):
		self.observers.discard( ( observer, notification ) )
		
	def clear(self):
		self.observers.clear()
		
	def notify( self, publisher ):
		for ( observer, notification ) in self.observers:
			notification( observer, publisher )