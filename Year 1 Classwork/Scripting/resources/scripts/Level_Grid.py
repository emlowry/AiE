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
		self.levelWidth = int( math.ceil(screenProperties['width']/ tileSize['width']) )
		self.levelHeight= int( math.ceil(screenProperties['height']/ tileSize['height']) )
		self.levelSize = self.levelWidth * (self.levelHeight+1)
		self.screenSize = ( self.levelWidth * self.tileSize['width'], self.levelHeight * self.tileSize['height'] )
		print "LevelSize :", self.levelWidth, " ", self.levelHeight
		self.levelTiles = [None] * int(self.levelSize)
		self.observers = ObserverList()
		
		for i in range(int(self.levelSize)):
			self.levelTiles[i] = Tile()
			self.levelTiles[i].x = self.tileSize['width'] * (i % int(self.levelWidth))
			self.levelTiles[i].y = self.tileSize['height'] * ( (int(i)/(int(self.levelWidth))))
	
	def tileHeight(self):
		return 0 if ( None == tileSize ) else self.tileSize['height']
	
	def tileWidth(self):
		return 0 if ( None == tileSize ) else self.tileSize['width']
	
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
		xGrid = int(xGrid) % self.levelWidth
		yGrid = int(yGrid) % self.levelHeight
		return( not self.levelTiles[ ( yGrid * self.levelWidth ) + xGrid ].shouldDraw() )

	def toCorners( self, xGrid, yGrid ):
		xMin = xGrid * self.tileSize['width']
		yMin = yGrid * self.tileSize['height']
		return ( xMin, yMin, xMin + self.tileSize['width'], yMin + self.tileSize['height'] )

	def tileBorder( self, xGrid, yGrid, xDir, yDir ):
		corner1x, corner1y, corner2x, corner2y = self.toCorners( xGrid, yGrid )
		if ( 0 == xDir and 0 == yDir ):
			return ( corner1x, corner1y, corner2x, corner2y )
		if ( 0 == xDir ):
			return ( corner1x, corner1y if ( yDir < 0 ) else corner2y,
                     corner2x, corner1y if ( yDir < 0 ) else corner2y )
		if ( 0 == yDir ):
			return ( corner1x if ( xDir < 0 ) else corner2x, corner1y,
                     corner1x if ( xDir < 0 ) else corner2x, corner2y )
		x = corner1x if ( xDir < 0 ) else corner2x
		y = corner1y if ( yDir < 0 ) else corner2y
		return ( x, y, x, y )

	def toGrid( self, xPixel, yPixel ):
		xGrid = int( math.floor(xPixel/self.tileSize['width']) )
		yGrid = int( math.floor(yPixel/self.tileSize['height']) )
		return ( xGrid, yGrid )

	def resolveGridSquare(self, xPos, yPos):
		xGridPos, yGridPos = self.toGrid( xPos, yPos )
		return (yGridPos * self.levelWidth) + xGridPos

	def obstacleIntersects( self, xGrid, yGrid, xPoint1, yPoint1, xPoint2, yPoint2 ):
		tileAspectRatio = float(self.tileSize['width']) / float(self.tileSize['height'])
		adjustedYPoint1 = yPoint1 * tileAspectRatio
		adjustedYPoint2 = yPoint2 * tileAspectRatio
		return Geometry.SegmentCircleIntersect( xPoint1, adjustedYPoint1, xPoint2, adjustedYPoint2,
                                                ( float(xGrid) + 0.5 ) * self.tileSize['width'],
                                                ( float(yGrid) + 0.5 ) * self.tileSize['width'],
                                                0.5 * self.tileSize['width'] )

	def getObstacles( self, xGrid, yGrid, xDir, yDir, bIgnoreStart = False ):
		obstacles = []
		if( 0 == xDir ):
			if( not bIgnoreStart and self.obstacleAt( xGrid, yGrid ) ):
				obstacles.append( ( xGrid, yGrid ) )
			if( self.obstacleAt( xGrid - 1, yGrid ) ):
				obstacles.append( ( xGrid - 1, yGrid ) )
			if( self.obstacleAt( xGrid - 1, yGrid + yDir ) ):
				obstacles.append( ( xGrid - 1, yGrid + yDir ) )
			if( self.obstacleAt( xGrid, yGrid + yDir ) ):
				obstacles.append( ( xGrid, yGrid + yDir ) )
			if( self.obstacleAt( xGrid + 1, yGrid + yDir ) ):
				obstacles.append( ( xGrid + 1, yGrid + yDir ) )
			if( self.obstacleAt( xGrid + 1, yGrid ) ):
				obstacles.append( ( xGrid + 1, yGrid ) )
		elif( 0 == yDir ):
			if( not bIgnoreStart and self.obstacleAt( xGrid, yGrid ) ):
				obstacles.append( ( xGrid, yGrid ) )
			if( self.obstacleAt( xGrid, yGrid - 1 ) ):
				obstacles.append( ( xGrid, yGrid - 1 ) )
			if( self.obstacleAt( xGrid + xDir, yGrid - 1 ) ):
				obstacles.append( ( xGrid + xDir, yGrid - 1 ) )
			if( self.obstacleAt( xGrid + xDir, yGrid ) ):
				obstacles.append( ( xGrid + xDir, yGrid ) )
			if( self.obstacleAt( xGrid + xDir, yGrid + 1 ) ):
				obstacles.append( ( xGrid + xDir, yGrid + 1 ) )
			if( self.obstacleAt( xGrid, yGrid + 1 ) ):
				obstacles.append( ( xGrid, yGrid + 1 ) )
		else:
			if( not bIgnoreStart and self.obstacleAt( xGrid, yGrid ) ):
				obstacles.append( ( xGrid, yGrid ) )
			if( self.obstacleAt( xGrid - xDir, yGrid + yDir ) ):
				obstacles.append( ( xGrid - xDir, yGrid + yDir ) )
			if( self.obstacleAt( xGrid, yGrid + yDir ) ):
				obstacles.append( ( xGrid, yGrid + yDir ) )
			if( self.obstacleAt( xGrid + xDir, yGrid + yDir ) ):
				obstacles.append( ( xGrid + xDir, yGrid + yDir ) )
			if( self.obstacleAt( xGrid + xDir, yGrid ) ):
				obstacles.append( ( xGrid + xDir, yGrid ) )
			if( self.obstacleAt( xGrid + xDir, yGrid - yDir ) ):
				obstacles.append( ( xGrid + xDir, yGrid - yDir ) )
		return obstacles

	def distanceToObstacle( self, xGrid, yGrid, xStart, yStart, xDir, yDir ):
		tileAspectRatio = float(self.tileSize['width']) / float(self.tileSize['height'])
		adjustedYStart = yStart * tileAspectRatio
		adjustedYDir = yDir * tileAspectRatio
		adjustedDistance = Geometry.RayCircleDistance( xStart, adjustedYStart, xDir, adjustedYDir,
                                                       ( float(xGrid) + 0.5 ) * self.tileSize['width'],
                                                       ( float(yGrid) + 0.5 ) * self.tileSize['width'],
                                                       0.5 * self.tileSize['width'] )
		return ( adjustedDistance if ( 1.0 == tileAspectRatio )
                 else adjustedDistance * math.sqrt( ( 1 + tileAspectRatio**-2 ) / 2 ) )

	# Returns true if there are no obstacles between the given position and the
	# given target, excluding the grid squares of the position and target if
	# indicated
	def lineOfSight( self, xPos, yPos, xTarget, yTarget, bIgnorePosition = False, bIgnoreTarget = False ):
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
		xInc = 1 if ( xGridPos < xGridTarget ) else -1
		yInc = 1 if ( yGridPos < yGridTarget ) else -1
		x = xGridPos
		y = yGridPos
		while( xMin <= x <= xMax and yMin <= y <= yMax ):
			if( self.obstacleAt( x, y ) and
				( not bIgnorePosition or x != xGridPos or y != yGridPos ) and
				( not bIgnoreTarget or x != xGridTarget or y != yGridTarget ) ):
				return False
			corner1x, corner1y, corner2x, corner2y = self.tileBorder( x, y, xInc, 0 )
			if( Geometry.SegmentsIntersect( xPos, yPos, xTarget, yTarget, corner1x, corner1y, corner2x, corner2y ) ):
				x += xInc
			else:
				corner1x, corner1y, corner2x, corner2y = self.tileBorder( x, y, 0, yInc )
				if( not Geometry.SegmentsIntersect( xPos, yPos, xTarget, yTarget, corner1x, corner1y, corner2x, corner2y ) ):
					x += xInc
				y += yInc
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
		self.otherImageName = "./images/Red_Desert_With_Rock.jpg"
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