import AIE
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
	
	def update(self, fDeltaTime):
		mouseX, mouseY = AIE.GetMouseLocation()
		
		if( AIE.GetMouseButton(0)  and (self.buttonPressed is False) ):
			self.buttonPressed = True
			tileIndex = int(self.resolveGridSquare(mouseX, mouseY))
			if( tileIndex >= 0 and tileIndex < self.levelSize ):
				self.levelTiles[tileIndex].setDraw()
				
		self.buttonPressed = not AIE.GetMouseButtonRelease(0)		
		
		
	def draw(self):
		for i in range( int(self.levelSize) ):
			if( self.levelTiles[i].shouldDraw() ):
				AIE.DrawSprite( self.levelTiles[i].getSpriteID() )
			else:
				AIE.DrawSprite( self.levelTiles[i].getOtherSpriteID() )

	def obstacleAt( self, xGrid, yGrid ):
		return( !self.levelTiles[ ( yGrid * self.levelWidth ) + xGrid ].shouldDraw() )

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

	def crossesObstacle( self, xPos, yPos, xTarget, yTarget ):
		xGridPos, yGridPos = self.toGrid( xPos, yPos )
		xGridTarget, yGridTarget = self.toGrid( xTarget, yTarget )
		if( xGridPos == xGridTarget && yGridPos == yGridTarget ):
			return False
		xMin = xGridPos if ( xGridPos < xGridTarget ) else xGridTarget
		yMin = yGridPos if ( yGridPos < yGridTarget ) else yGridTarget
		xMax = xGridPos if ( xGridPos > xGridTarget ) else xGridTarget
		yMax = yGridPos if ( yGridPos > yGridTarget ) else yGridTarget
		for x in range( xMin, xMax + 1 ):
			for y in range( yMin, yMax + 1 ):
				if( ( x != xGridPos || y != yGridPos ) && ( x != xGridTarget || x != yGridTarget ) ):
					corner1x, corner1y, corner2x, corner2y = self.toCorners( x, y )
	
	def cleanUp(self):
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