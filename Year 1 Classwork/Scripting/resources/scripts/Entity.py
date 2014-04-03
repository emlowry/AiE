import AIE
import game
import math
import Level_Grid

#Tank Entity
#   A simple entity that can be placed on the screen with a right click, you should modify this so that the tank can be told to 
#   navigate to a point instead of instantly move.

class TankEntity:

	def __init__(self, level):
		self.level = level
		self.Position = ( 1200, 600 )
        self.Velocity = ( 0, 0 )
		self.Target = ( 1200, 600 )
		self.Waypoint = None
		self.Rotation = 0
		self.spriteName = "./images/PlayerTanks.png"
		self.size = (57, 72 )
		self.origin = (0.5, 0.5)
		self.spriteID = AIE.CreateSprite( self.spriteName, self.size[0], self.size[1], self.origin[0], self.origin[1], 71.0/459.0, 1.0 - 72.0/158.0, 128/459.0, 1.0 , 0xff, 0xff, 0xff, 0xff )
		print "spriteID", self.spriteID
		level.register( self, TankEntity.recalculateRoute )
		self.turret = Turret(self)

	def squaredDistanceFromWaypoint( self ):
		if( self.Waypoint == None )
			return 0.0;
		x = self.Position[0] - self.Waypoint[0]
		y = self.Position[1] - self.Waypoint[1]
        return x*x + y*y

	def recalculateRoute( self, level ):
		print "Recalculating route from position ", self.Position, " to target ", self.Target
		self.Rotation = math.atan2( self.Position[0] - self.Target[0], self.Position[1] - self.Target[1] )
		if( level.lineOfSight( self.Position[0], self.Position[1], self.Target[0], self.Target[1], True, True ) ):
			self.Waypoint = self.Target
		else:
			self.Waypoint = None

	def arrive( self, xPos, yPos, slowDistance, fDeltaTime ):
		squaredDistance = self.squaredDistanceFromWaypoint()
		if( squaredDistance > slowDistance * slowDistance ):
			self.Position = ( xPos, yPos )
		else:
			self.Position = ( xPos * fDeltaTime + self.Position[0] * ( 1.0 - fDeltaTime ),
							  yPos * fDeltaTime + self.Position[1] * ( 1.0 - fDeltaTime ) )
		
	def update(self, fDeltaTime ):
		mouseX, mouseY = AIE.GetMouseLocation()
		if( AIE.GetMouseButton(1)  ):
			self.Target = ( mouseX, mouseY )
			self.recalculateRoute( self.level )
		if( self.Waypoint != None ):
			self.seek( self.Waypoint[0], self.Waypoint[1], fDeltaTime )
		AIE.PositionSprite( self.spriteID, math.degrees( self.Rotation ), self.Position[0], self.Position[1] )
		self.turret.update(fDeltaTime)
	
	def draw(self):
		
		AIE.DrawSprite( self.spriteID )
		self.turret.draw()
		
	def getImageName(self):
		return self.imageName
		
	def getState(self):
		return self.state
	
	def getSpriteID(self):
		return self.spriteID
		
	def setSpriteID(self, a_spriteID):
		self.spriteID = a_spriteID
	
	def getPosition(self):
		return self.Position

	def cleanUp(self):
		self.turret.cleanUp()
		AIE.DestroySprite( self.spriteID )
		
#Turret
#    This is an Entity Object that has an owner, it is up to you to implement inheritance (BaseEntity->Turret) 
#    The Turret's position is based on the location of it's owner, if it's owner (in this scenario a Tank) is moveable
#    The turret will move with it's base/owner

class Turret:
	
	def __init__(self, owner):
		self.owner = owner
		self.Position = ( 0, 0 )
		self.Rotation = 0
		self.spriteName = "./images/PlayerTanks.png"
		self.size = (29, 60 )
		self.origin = (0.55, 0.75)
		self.spriteID = AIE.CreateSprite( self.spriteName, self.size[0], self.size[1], self.origin[0], self.origin[1], 129.0/459.0, 1.0 - 61.0/158.0, 157.0/459.0, 1.0 , 0xff, 0xff, 0xff, 0xff )
		print "spriteID", self.spriteID
	
	def update(self, fDeltaTime):
		turretLocation = self.owner.getPosition()
		mouseX, mouseY = AIE.GetMouseLocation()
		rotation = math.atan2( turretLocation[0] - mouseX, turretLocation[1] - mouseY )
		AIE.PositionSprite( self.spriteID, math.degrees( rotation ), turretLocation[0], turretLocation[1] )
		
	def draw(self):
		AIE.DrawSprite( self.spriteID )
	
	def	cleanUp(self):
		AIE.DestroySprite( self.spriteID )
		