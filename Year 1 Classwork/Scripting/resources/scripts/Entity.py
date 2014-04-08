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
		self.Position = ( 600, 300 )
		self.Velocity = ( 0, 0 )
		self.Target = ( 600, 300 )
		self.Waypoint = None
		self.Rotation = 0
		self.spriteName = "./images/PlayerTanks.png"
		self.size = (57, 72 )
		self.origin = (0.5, 0.5)
		self.spriteID = AIE.CreateSprite( self.spriteName, self.size[0], self.size[1], self.origin[0], self.origin[1], 71.0/459.0, 1.0 - 72.0/158.0, 128/459.0, 1.0 , 0xff, 0xff, 0xff, 0xff )
		print "spriteID", self.spriteID
		level.register( self, TankEntity.recalculateRoute )
		self.turret = Turret(self)

	def recalculateRoute( self, level ):
		print "Recalculating route from position ", self.Position, " to target ", self.Target
		if( self.Position != self.Target and
            level.lineOfSight( self.Position[0], self.Position[1], self.Target[0], self.Target[1], True, True ) ):
			self.Waypoint = self.Target
		else:
			self.Waypoint = None

	def isWithin( self, xPos, yPos, radius ):
		if( xPos == self.Position[0] and yPos == self.Position[1] ):
			return True
		squaredDistance = ( self.Position[0] - xPos )**2 + ( self.Position[1] - yPos )**2
		if( squaredDistance < radius**2 ):
			return True
		return False

	def slowWithin( self, xPos, yPos, radius, strength ):
		if( xPos == self.Position[0] and yPos == self.Position[1] ):
			return ( -self.Velocity[0] * strength, -self.Velocity[1] * strength )
		if( not self.isWithin( xPos, yPos, radius ) ):
			return ( 0.0, 0.0 )
		squaredDistance = ( self.Position[0] - xPos )**2 + ( self.Position[1] - yPos )**2
		breakStrength = ( 1 - squaredDistance/radius**2 ) * strength
		return ( -self.Velocity[0] * breakStrength, -self.Velocity[1] * breakStrength )

	def seek( self, xPos, yPos ):
		displacement = ( self.Position[0] - xPos, self.Position[1] - yPos )
		squaredDistance = displacement[0]**2 + displacement[1]**2
		if( squaredDistance <= 0.0 ):
			return ( 0.0, 0.0 )
		distance = math.sqrt( squaredDistance )
		speed = math.sqrt( self.Velocity[0]**2 + self.Velocity[1]**2 )
		return ( -displacement[0]*speed/distance - self.Velocity[0],
                 -displacement[1]*speed/distance - self.Velocity[1] )

	def accelerateTo( self, speed, acceleration ):
		speedSquared = self.Velocity[0]**2 + self.Velocity[1]**2
		if( speedSquared == speed**2 ):
			return ( 0.0, 0.0 )
		if( speedSquared <= 0.0 ):
			return ( math.cos( self.Rotation ) * acceleration,
                     math.sin( self.Rotation ) * acceleration )
		currentSpeed = math.sqrt( speedSquared )
		if( currentSpeed < speed ):
			return ( self.Velocity[0] * acceleration / currentSpeed,
                     self.Velocity[1] * acceleration / currentSpeed )
		return ( -self.Velocity[0] * acceleration / currentSpeed,
                 -self.Velocity[1] * acceleration / currentSpeed )

	def arriveWithin( self, xPos, yPos, radius, speed, acceleration ):
		seek = self.seek( xPos, yPos )
		if( self.isWithin( xPos, yPos, radius ) ):
			slow = self.slowWithin( xPos, yPos, radius, acceleration )
			return ( seek[0] + slow[0], seek[1] + slow[1] )
		accel = self.accelerateTo( speed, acceleration )
		return ( seek[0] + accel[0], seek[1] + accel[1] )

	def update(self, fDeltaTime ):

        # recalculate route if right mouse button is clicked
		mouseX, mouseY = AIE.GetMouseLocation()
		if( AIE.GetMouseButton(1) ):
			self.Target = ( mouseX, mouseY )
			self.recalculateRoute( self.level )

        # calculate acceleration
		acceleration = None
		if( None == self.Waypoint ):
			acceleration = self.accelerateTo( 0, 200 )
		else:
			acceleration = self.arriveWithin( self.Waypoint[0], self.Waypoint[1], 20, 200, 200 )
		print "acceleration: ", acceleration

        # calculate position, velocity, and rotation
		self.Position = ( self.Position[0] + self.Velocity[0]*fDeltaTime + acceleration[0]*fDeltaTime**2/2,
                          self.Position[1] + self.Velocity[1]*fDeltaTime + acceleration[1]*fDeltaTime**2/2 )
		self.Velocity = ( self.Velocity[0] + acceleration[0] * fDeltaTime,
                          self.Velocity[1] + acceleration[1] * fDeltaTime )
		if( self.Velocity[0] != 0.0 or self.Velocity[1] != 0.0 ):
			self.Rotation = math.atan2( -self.Velocity[1], self.Velocity[0] )

        # move OpenGL sprite and turret sprite
		AIE.PositionSprite( self.spriteID, math.degrees( self.Rotation - ( math.pi / 2 ) ), self.Position[0], self.Position[1] )
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
		rotation = math.atan2( -mouseY + turretLocation[1], mouseX - turretLocation[0] )
		AIE.PositionSprite( self.spriteID, math.degrees( rotation - ( math.pi / 2 ) ), turretLocation[0], turretLocation[1] )
		
	def draw(self):
		AIE.DrawSprite( self.spriteID )
	
	def	cleanUp(self):
		AIE.DestroySprite( self.spriteID )
		